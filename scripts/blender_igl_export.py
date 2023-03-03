# Given a geometry, the armature and the root bone
# this script will export the .obj, .tgf and .dmat files 
# for mesh, skeleton and skinning respectively.
# You can load this script directly from within blender
# and hit run 

import bpy
import logging
import numpy as np
import struct

from bpy_extras.io_utils import (
    axis_conversion,
    ExportHelper
)

from pathlib import Path
path_string = '~/Documents/blender_igl_export.log'

# LOGGING SETUP
logging.basicConfig(filename=str(Path(path_string).expanduser()),
                    filemode='w', level=logging.DEBUG, force=True)

logger = logging.getLogger(__name__)


# GLOBAL CONSTANTS
IGL_AXIS_FORWARD = "-Z"
IGL_AXIS_UP = "Y"


class IGLSkeleton:
    def __init__(self):
        # A bone is an unconnected entity
        # Each bone will have a [x, y, z]
        self.bones = []

        # A parent / joint is a connection of 2 bones.
        # Each parent is a connection from parent index to child index
        self.parents = set()

        # Contains a mapping from blender bone name to IGL bone index
        self.blender_bone_mapping = {}

    
    @property
    def n_limbs(self):
        return len(self.parents)
    
    @property
    def n_bones(self):
        return len(self.bones)
    
    def _convert_coordinate_system(self, location):
        """
        Receives a location as x, y and z in Blender Coordinate System (Z Up, Z forward)
        and converts it to a more traditional coordinate system (Z Up,)
        """
        global_matrix = axis_conversion(
            to_forward=IGL_AXIS_FORWARD,
            to_up=IGL_AXIS_UP,
        ).to_4x4()

        affine_location = location.to_4d()
        transformed_location = global_matrix @ affine_location

        return transformed_location
    
    def add_bone(self, bone_name, location):
        if bone_name in self.blender_bone_mapping:
            logger.error(f"{bone_name} already in IGL Skeleton")
            return

        location = self._convert_coordinate_system(location)
        
        self.bones.append([location[0], location[1], location[2]])
        self.blender_bone_mapping[bone_name] = len(self.bones) - 1

        logger.info(f"Bone {bone_name} added at {self.blender_bone_mapping[bone_name]}: {self.bones[-1]}")
    
    def add_parent(self, parent_bone_name, child_bone_name):
        if parent_bone_name not in self.blender_bone_mapping:
            logger.error(f"Parent {parent_bone_name} not in IGL Skeleton")
            return

        if child_bone_name not in self.blender_bone_mapping:
            logger.error(f"Child {child_bone_name} not in IGL Skeleton")
            return

        edge_tuple = (self.blender_bone_mapping[parent_bone_name], self.blender_bone_mapping[child_bone_name])
        if edge_tuple in self.parents:
            logger.error(f"{parent_bone_name}-{child_bone_name} pairing already in IGL Skeleton")
            return

        reversed_edge_tuple = (self.blender_bone_mapping[child_bone_name], self.blender_bone_mapping[parent_bone_name])
        if reversed_edge_tuple in self.parents:
            logger.warning(f"{parent_bone_name}-{child_bone_name} introduces a cylical bone structure which maybe unsupported")

        self.parents.add(edge_tuple)

        logger.info(f"{parent_bone_name}-{child_bone_name} added to IGL skeleton")

    def export(self, file_name_without_ext):
        with open(f"{file_name_without_ext}.tgf", "w") as skeleton_writer:
            for bone_idx, bone in enumerate(self.bones):
                skeleton_writer.write(f"{bone_idx + 1} {bone[0]} {bone[1]} {bone[2]}\n")
            
            skeleton_writer.write("#")

            for parent in self.parents:
                skeleton_writer.write(f"\n{parent[0] + 1} {parent[1] + 1}")
            
            skeleton_writer.write("\n#")


class IGLDeformableMesh:
    def __init__(self, geometry, igl_skeleton):
        super().__init__()
        self.geometry = geometry
        self.skeleton = igl_skeleton
        self.skinning = np.zeros((len(self.geometry.data.vertices), self.skeleton.n_limbs), dtype=np.float64)

        self._parse_skinning_data()

    def _parse_skinning_data(self):
        for vert_idx in range(self.skinning.shape[0]):
            for vertex_group in self.geometry.vertex_groups:
                if vertex_group.name not in self.skeleton.blender_bone_mapping:
                    logger.error(f"{vertex_group.name} is a vertex group but the bone doesn't exist")
                    return

                bone_idx = self.skeleton.blender_bone_mapping[vertex_group.name]
                try:
                    self.skinning[vert_idx, bone_idx] = vertex_group.weight(vert_idx)
                except RuntimeError:
                    self.skinning[vert_idx, bone_idx] = 0.0
        
        logger.info(
            f"Constructed {self.skinning.shape} skinning matrix. Max: {self.skinning.max()}, Min: {self.skinning.min(0)}")
        
    def export(self, file_name_without_ext):
        self._export_weights(file_name_without_ext)
        self._export_obj(file_name_without_ext)

        if not self._validate_obj(file_name_without_ext):
            logger.error("Obj Validation Failed")
        else:
            logger.info("Skinning Matrix and OBJ successfully exported")

    
    def _export_weights(self, file_name_without_ext):
        with open(f"{file_name_without_ext}.dmat", "wb") as skinning_binary_writer:
            skinning_binary_writer.write(
                bytes(bytearray("0 0\n", encoding='ascii'))
            )

            skinning_binary_writer.write(bytes(
                bytearray(f"{self.skinning.shape[1]} {self.skinning.shape[0]}\n", encoding='ascii')
            ))

            flattened_skinning_matrix = self.skinning.flatten(order='F').tolist()
            s = struct.pack('d'*len(flattened_skinning_matrix), *flattened_skinning_matrix)
            skinning_binary_writer.write(s)

    def _export_obj(self, file_name_without_ext):
        bpy.ops.export_scene.obj(
            filepath=f"{file_name_without_ext}.obj",
            check_existing=False,
            filter_glob='*.obj;*.mtl',
            use_selection=False,
            use_animation=False,
            use_mesh_modifiers=True,
            use_edges=False,
            use_smooth_groups=False,
            use_smooth_groups_bitflags=False,
            use_normals=True,
            use_uvs=True,
            use_materials=True,
            use_triangles=False,
            use_nurbs=False,
            use_vertex_groups=False,
            use_blen_objects=True,
            group_by_object=False,
            group_by_material=True,
            keep_vertex_order=True,
            global_scale=1.0,
            path_mode='AUTO',
            axis_forward=IGL_AXIS_FORWARD,
            axis_up=IGL_AXIS_UP
        )

    def _validate_obj(self, file_name_without_ext):
        is_valid = True
        with open(f"{file_name_without_ext}.obj", "r") as obj_reader:
            all_lines = obj_reader.readlines()
            for idx, line in enumerate(all_lines):
                split = line.split(" ")
                if split[0] == 'f':
                    # len should be 4 including 4
                    if len(split) != 4:
                        logger.error(f"Line {idx+1} has illegal face definition. Triangulate your mesh")
                        is_valid = False

        return is_valid

# FILE BROWSER SETUP
class IGLExportHelper(bpy.types.Operator, ExportHelper):
    bl_idname = 'igl.export_helper'
    bl_label = 'Export'
    bl_options = {'PRESET', 'UNDO'}

    filename_ext = ''

    def _begin_export(self, context, file_path):
        if len(bpy.context.selected_objects) != 1:
            logger.error("No support for 0 or multiple objects selected. Select the object at the highest level")
            return

        parent = bpy.context.selected_objects[0]
        logger.info(f"Exporting a Skinned Mesh @ {parent.name}")
        
        if len(parent.children) != 1:
            logger.error("We support skinning of a single geometry only")
            return
        
        if parent.name not in bpy.data.armatures:
            logger.error(f"Expected to have {parent.name} as the corresponding armature name as well")
            return
        
        geometry = parent.children[0]
        armature = bpy.data.armatures[parent.name]
        
        logger.info(f"Processing Armature with {len(armature.bones)} bones")
        root_bone = "root"
        if root_bone not in armature.bones:
            logger.error(f"Please mark the highest level node as {root_bone}")
            return

        bones_to_process = [armature.bones[root_bone]]
        igl_skeleton = IGLSkeleton()

        while len(bones_to_process) > 0:
            bone = bones_to_process.pop()
            igl_skeleton.add_bone(bone.name, bone.head_local)
            if bone.parent is not None:
                # At this point the parent should have already been added to IGL Skeleton
                igl_skeleton.add_parent(bone.parent.name, bone.name)

            if len(bone.children) == 0:
                tail_bone_name = f"{bone.name}_tail"
                igl_skeleton.add_bone(tail_bone_name, bone.tail_local)
                igl_skeleton.add_parent(bone.name, tail_bone_name)
            else:
                for child in bone.children:
                    bones_to_process.append(child)

        igl_skeleton.export(file_path)

        deformable_mesh = IGLDeformableMesh(geometry, igl_skeleton)
        deformable_mesh.export(file_path)

    def _get_valid_asset_path(self, filepath):
        if len(filepath.split('.')) > 1:
            # Remove any extension
            return filepath.split('.')[0]
        elif filepath[-1] == "/":
            # Use a temporary name if a folder was selected.
            return filepath + "tmp"
        return filepath

    def execute(self, context):
        self._begin_export(context, self._get_valid_asset_path(self.filepath))
        return {'FINISHED'}

if __name__ == "__main__":
    bpy.utils.register_class(IGLExportHelper)
    bpy.ops.igl.export_helper('INVOKE_DEFAULT')
    