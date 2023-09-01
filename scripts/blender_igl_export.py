# Given a geometry, the armature and the root bone
# this script will export the .obj, .tgf and .dmat files 
# for mesh, skeleton and skinning respectively.
# You can load this script directly from within blender
# and hit run 

import bpy
import io
import logging
import numpy as np
import struct

from bpy_extras.io_utils import (
    axis_conversion,
    ExportHelper
)


from collections import OrderedDict
from pathlib import Path

# LOGGING SETUP
class ExportFileHandler(logging.FileHandler):
    def __init__(self) -> None:
        self._log_file = str(Path('~/Documents/blender_igl_export.log').expanduser())
        super().__init__(
            self._log_file,
            "w",
            None,
            False,
            'backslashreplace')
        
        self._n_errors = 0
        self._n_warns = 0

    @property
    def log_file(self):
        return self._log_file
    
    @property
    def num_warns(self):
        return self._n_warns
    
    @property
    def num_errors(self):
        return self._n_errors

    def emit(self, record) -> None:
        if record.levelno == logging.ERROR or record.levelno == logging.CRITICAL:
            self._n_errors += 1
        elif record.levelno == logging.WARN or record.levelno == logging.WARNING:
            self._n_warns += 1

        return super().emit(record)

log_handler = ExportFileHandler()
logging.basicConfig(handlers=[log_handler], level=logging.DEBUG, force=True)

logger = logging.getLogger(__name__)


# GLOBAL CONSTANTS
IGL_AXIS_FORWARD = "-Z"
IGL_AXIS_UP = "Y"
EMPTY_ARRAY = np.array([])

GLOBAL_MATRIX = axis_conversion(
    to_forward=IGL_AXIS_FORWARD,
    to_up=IGL_AXIS_UP,
).to_4x4()

def _convert_location_coordinate_system(location):
        """
        Receives a location in Blender Coordinate System (Z Up, Y forward)
        and converts it to a more traditional coordinate system (Y Up, -Z forward)
        """
        transformed_location = GLOBAL_MATRIX @ location.to_4d()

        return transformed_location[:-1]
    
def _convert_transform_coordinate_system(transform):
    """
    Receives a transform as 4x4 affine matrix in Blender Coordinate System (Z Up, Y forward)
    and converts it to a more traditional coordinate system (Y Up, -Z forward)
    """
    transformed_location = GLOBAL_MATRIX @ transform

    return transformed_location

def _export_matrix_as_dmat(file_name_without_ext, matrix):
        """
        Given a numpy array as 2D matrix this function will write out
        the matrix to a .dmat using the libigl specification.
        """
        if len(matrix.shape) != 2:
            logger.error(f"Dmat export expected 2D array. Got {matrix.shape}")

        with open(f"{file_name_without_ext}.dmat", "wb") as binary_writer:
            binary_writer.write(
                bytes(bytearray("0 0\n", encoding='ascii'))
            )

            binary_writer.write(bytes(
                bytearray(f"{matrix.shape[1]} {matrix.shape[0]}\n", encoding='ascii')
            ))

            flattened_matrix = matrix.flatten(order='F').tolist()
            s = struct.pack('d'*len(flattened_matrix), *flattened_matrix)
            binary_writer.write(s)


class IGLSkeleton:
    def __init__(self):
        # A bone is an unconnected entity
        # Each bone will store a 4x4 transform relative to it's
        # armature parent
        self.bones = []
        # Will just store the xyz of the bone
        self.head_bone_transforms = {}
        
        # A parent / joint is a connection of 2 bones.
        # Each parent is a connection from parent index to child index
        self.parents = OrderedDict()

        # Contains a mapping from blender bone name to IGL bone index
        self.blender_bone_mapping = {}
    
    @property
    def n_limbs(self):
        return len(self.parents)
    
    @property
    def n_bones(self):
        return len(self.bones)
    
    @property
    def bind_pose(self):
        # Hold a numpy array for bind pose.
        # We will not export the bind pose, but if animation
        # is exported, this bind_pose can be used or exported 
        # independently
        if self.n_limbs == 0:
            logger.error("Requested bind pose when we have no limbs")
            return EMPTY_ARRAY

        bind_pose_transforms = np.tile(
            np.eye(4, dtype=np.float64), (self.n_limbs, 1, 1))
        
        transform_idx = 0
        # NOTE: this ordering won't change, so safe to use this
        for parent, _ in self.parents.items():
            bone_idx = parent[0]

            if bone_idx not in self.head_bone_transforms:
                logger.error(f"{bone_idx} not in head bone transforms. How did it become a parent?")
                return EMPTY_ARRAY
            
            # Does a very simple copy of the selected bone transforms
            bind_pose_transforms[transform_idx, :, :] = self.head_bone_transforms[bone_idx]
            transform_idx += 1
        
        return bind_pose_transforms
    
    def add_bone(self, bone_name, location, transform=None):
        if bone_name in self.blender_bone_mapping:
            logger.error(f"{bone_name} already in IGL Skeleton")
            return

        location = _convert_location_coordinate_system(location)
        
        self.bones.append(location)
        self.blender_bone_mapping[bone_name] = len(self.bones) - 1

        if transform is not None:
            transform = np.array(
                _convert_transform_coordinate_system(transform), dtype=np.float64)
            
            self.head_bone_transforms[len(self.bones) - 1] = transform

        logger.info(f"BONE {bone_name} added at {self.blender_bone_mapping[bone_name]}: {self.bones[-1]}")
    
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

        # Store the parent bone name, because this can be used to extract limb transform information
        self.parents[edge_tuple] = parent_bone_name

        logger.info(f"LIMB {parent_bone_name}-{child_bone_name} added to IGL skeleton")

    def export(self, file_name_without_ext):
        with open(f"{file_name_without_ext}.tgf", "w") as skeleton_writer:
            for bone_idx, bone in enumerate(self.bones):
                skeleton_writer.write(
                    f"{bone_idx + 1} {bone[0]} {bone[1]} {bone[2]}\n")
            
            skeleton_writer.write("#")

            for parent, _ in self.parents.items():
                # Adding 1 to the end of the write to indicate this is a bone edge.
                skeleton_writer.write(f"\n{parent[0] + 1} {parent[1] + 1} 1")
            
            skeleton_writer.write("\n#")
        
        logger.info(f"SKELETON exported in {file_name_without_ext}.tgf")

        igl_bind_pose = self.bind_pose[:, :3, :]  # J X 3 X 4 ... last row of affine matrix not needed
        igl_bind_pose = igl_bind_pose.transpose((0, 2, 1))  # J X 4 X 3 ... igl standard

        # Save bind pose as npy
        np.save(f"{file_name_without_ext}_bind_pose.npy", igl_bind_pose)
        logger.info(f"BIND POSE {igl_bind_pose.shape} exported in {file_name_without_ext}_bind_pose.npy")

        # Save bind pose as dmat
        # J*4 X 3 ... stack the transforms
        bind_pose_flat = igl_bind_pose.reshape((-1, igl_bind_pose.shape[2]))
        _export_matrix_as_dmat(f"{file_name_without_ext}_bind_pose.dmat", bind_pose_flat)
        logger.info(f"BIND POSE {bind_pose_flat.shape} exported in {file_name_without_ext}_bind_pose.dmat")


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
        
    def export(self, file_name_without_ext, export_mesh=True, export_weights=True):
        if export_weights:
            self._export_weights(file_name_without_ext)
            logger.info("Skinning Matrix successfully exported")

        if export_mesh:
            self._export_obj(file_name_without_ext)
            if not self._validate_obj(file_name_without_ext):
                logger.error("Obj Validation Failed")
            else:
                logger.info("OBJ successfully exported")

    
    def _export_weights(self, file_name_without_ext):
        _export_matrix_as_dmat(file_name_without_ext, self.skinning)

    def _export_obj(self, file_name_without_ext):
        # Always Export from Frame 0
        current_frame = bpy.context.scene.frame_current
        bpy.context.scene.frame_set(0)

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

        # Reset the frame
        bpy.context.scene.frame_set(current_frame)

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
    
class IGLAnimation:
    def __init__(self, igl_skeleton, parent_armature, start_frame, end_frame):
        self.skeleton = igl_skeleton
        self.armature = parent_armature
        self.action = parent_armature.animation_data.action
        
        end_key_frame = 1
        for fcu in self.action.fcurves:
            for idx, keyframe in enumerate(fcu.keyframe_points):
                end_key_frame = max(end_key_frame, keyframe.co[0])

        self.start_frame = int(min(start_frame, end_key_frame)) # Can't start beyond the last key frame
        self.end_frame = int(min(end_frame, end_key_frame)) # Can't end beyond the last key frame

        logger.info(f"Ready to Export Animation frames [{self.start_frame}, {self.end_frame}]")

    def _export_npy(self, filepath, animation):
        np.save(f"{filepath}_animation.npy", animation)
        logger.info(
            f"ANIMATION ({animation.shape}) exported as npy")
    
    def _export_dmat(self, filepath, animation):
        # Frames X J*4*3
        animation_flat = animation.reshape((animation.shape[0], -1))
        animation_flat = animation_flat.transpose() # J*4*3 X Frames

        _export_matrix_as_dmat(f"{filepath}_animation", animation_flat)
        
        logger.info(
            (f"ANIMATION [{animation_flat.shape} column ordered from {animation.shape}] "
             "exported as dmat"))
        
    def _get_bind_pose_relative_animation(self, bind_pose, animation):
        # Given a bind pose and a list of animation frames
        # where each frame has world transforms of the bones
        # this function will apply the inverse of the bind pose to get
        # relative frames.
        inverse_bind_pose = np.linalg.inv(bind_pose)
        relative_animation = [frame @ inverse_bind_pose for frame in animation]

        return relative_animation


    def export(self, filepath):
        # Store the current frame in UI to restore after export
        current_frame = bpy.context.scene.frame_current

        animation = []
        bpy.context.window_manager.progress_begin(0, self.end_frame + 1)
        bpy.context.window_manager.progress_update(0)
        for frame in range(self.start_frame, self.end_frame + 1):
            bpy.context.scene.frame_set(frame)

            pose = []
            # NOTE: This ordering will be consistent with bind_pose because parents
            # is an OrderedDict
            for _, parent_name in self.skeleton.parents.items():
                bone = self.armature.pose.bones[parent_name]
                bone_transform = _convert_transform_coordinate_system(bone.matrix)
                pose.append(bone_transform)
            
            animation.append(pose)
            bpy.context.window_manager.progress_update(frame)

        # Restore UI active frame
        bpy.context.scene.frame_set(current_frame)

        # Make IGL ready bind pose
        bind_pose = self.skeleton.bind_pose

        # Make IGL ready animation
        igl_animation = np.array(self._get_bind_pose_relative_animation(bind_pose, animation))
        igl_animation = igl_animation[:, :, :3, :]  # Frames X J X 3 X 4 ... last row of affine matrix not needed
        igl_animation = igl_animation.transpose((0, 1, 3, 2))  # Frames X J X 4 X 3 ... igl standard

        self._export_npy(filepath, igl_animation)
        self._export_dmat(filepath, igl_animation)


# FILE BROWSER SETUP
class IGLExportHelper(bpy.types.Operator, ExportHelper):
    bl_idname = 'igl.export_helper'
    bl_label = 'Export'
    
    filename_ext = ''
    
    export_skeleton: bpy.props.BoolProperty(
        name="Export Skeleton",
        description="Exports a tgf with bones and parent relationships",
        default=True
    )

    export_skinning: bpy.props.BoolProperty(
        name="Export Skinning",
        description="Exports a dmat with a dense matrix of vertex influence weights per bone (#V x #J)",
        default=True
    )

    export_mesh: bpy.props.BoolProperty(
        name="Export Mesh",
        description="Exports a obj containing the mesh that has been skinned",
        default=True
    )

    export_animation: bpy.props.BoolProperty(
        name="Export Animation",
        description="Exports a npy or dmat with bind pose and animation data",
        default=True
    )

    anim_start: bpy.props.IntProperty(
        name="Animation Start Frame",
        description="Starting animation frame for export",
        default=1, min=1, max=300000
    )
    
    anim_end: bpy.props.IntProperty(
        name="Animation End Frame",
        description="Ending animation frame for export",
        default=250, min=0, max=300000
    )
    

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

        bones_to_process = [armature.
                            bones[root_bone]]
        igl_skeleton = IGLSkeleton()

        while len(bones_to_process) > 0:
            bone = bones_to_process.pop()
            igl_skeleton.add_bone(bone.name, bone.head_local, bone.matrix_local)
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

        deformable_mesh = IGLDeformableMesh(geometry, igl_skeleton)

        if self.export_skeleton:
            igl_skeleton.export(file_path)
        
        if self.export_mesh or self.export_skinning:
            deformable_mesh.export(file_path, self.export_mesh, self.export_skinning)
        
        if self.export_animation:
            if parent.animation_data is None:
                logger.error("Requested to export animation but no animation data found")
            else:
                animation = IGLAnimation(igl_skeleton, parent, self.anim_start, self.anim_end)
                animation.export(file_path)

        self.report({'INFO'}, (
            f"Finished Export to {file_path}."
            f" Errors: {log_handler.num_errors}, Warnings: {log_handler.num_warns}"
        ))
        self.report({'INFO'}, f"Log dumped to {log_handler.log_file}")

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
    