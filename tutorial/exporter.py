import pydoc
import meshplot
import re
import queue
import tempfile

packages = queue.Queue()
packages.put("igl")

docs = ""


pattens_to_skip = [
	"R90 ",
	"M(e,e)",
	"for(int",
	"if(",
	"assert(",
	"E(e,1))",
	" F(f, :) ",
	"F(f,:) ",
	"cur_energy(OPTIONAL)",
	"d(A, B) = max(",
	"d(A,B)",
	"per_face_normals(V,F,Vector3d(1,1,1)",
	"the number of positively",
	"trace(",
	"Z(known,:)",
	"kron(ones(",
	"E(i,K(i))",
	"I(i) == E(J(i),K(i",
	"FF(I,:) = ",
	"f(X)"
]

def format_data(data):
	global docs
	docs += "\n| | |\n|-|-|\n"
	if "Parameters" in data:
		docs += "|Parameters| {} |\n".format(data["Parameters"].strip().replace("\n", "</br>").replace("#", r"\#"))
	if "Returns" in data and len(data["Returns"].strip()) > 0:
		docs += "|Returns| {} |\n".format(data["Returns"].strip().replace("\n", "</br>").replace("#", r"\#"))
	if "See also" in data and len(data["See also"].strip()) > 0 and data["See also"].strip() != "None":
		docs += "|See also| {} |\n".format(data["See also"].strip().replace("\n", "</br>").replace("#", r"\#"))
	if "Notes" in data and len(data["Notes"].strip()) > 0 and data["Notes"].strip() != "None":
		docs += "|Notes| {} |\n".format(data["Notes"].strip().replace("\n", "</br>").replace("#", r"\#"))
	if "Examples" in data and len(data["Examples"].strip()) > 0:
		docs += "\n**Examples**\n```python\n{}\n```\n".format(data["Examples"].strip().replace(">>> ", "").replace(">>>", ""))

	docs += "\n\n"

prevvv = None

while not packages.empty():
	package = packages.get()

	if prevvv == package:
		continue

	prevvv = package

	with tempfile.NamedTemporaryFile(suffix=".md") as tmp_file:
		with open(tmp_file.name, "w") as f:
			pydoc.doc(package,output=f)

		with open(tmp_file.name, "r") as f:
			lines = f.read()

	is_function = False

	if "PACKAGE CONTENTS" in lines:
		process = False

		for line in iter(lines.splitlines()):
			line = line.strip()

			if len(line) == 0:
				continue

			if "PACKAGE CONTENTS" in line:
				process = True
				continue

			if "FUNCTIONS" in line:
				is_function = True
				continue

			if line[0] == '|':
				continue

			if "FILE" in line:
				is_function = False
				break

			if "DATA" in line:
				is_function = False

			if not process:
				continue
			if len(line) <= 0:
				continue

			if is_function:
				is_func = re.match(r'^\w+\(.*\)', line)
				if is_func:
					packages.put(package + "." + line.split('(', 1)[0])
			else:
				if line != "pyigl":
					packages.put(package + "." + line)

		continue
	if "CLASSES" in lines:
		process = False


		for line in iter(lines.splitlines()):
			line = line.strip()

			if "CLASSES" in line:
				process = True
				continue

			if "FILE" in line:
				break

			if not process:
				continue
			if len(line) <= 0:
				continue

			if "class " in line:
				break
			if "builtins.object" in line:
				continue

			packages.put(package + "." + line)

		continue

	lines = lines.replace("pybind11_builtins.pybind11_object", "")
	lines = lines.replace("builtins.object", "")
	lines = lines.replace("|", "")
	# lines = lines.replace("class ", "## class ")
	lines = lines.replace("method of builtins.PyCapsule instance", "")
	lines = lines.replace("self, ", "")
	lines = lines.replace("self", "")
	lines = lines.replace(" -> None", "")
	lines = lines.replace("[float64[m, n]]", "")
	lines = lines.replace("[int32[m, n]]", "")

	tmp = ""

	skipping = False
	next_mark = False
	skip_next = False

	for line in iter(lines.splitlines()):
		line = line.strip()
		if skip_next:
			skip_next = False
			continue
		if len(line) <= 0:
			continue

		if "Python Library Documentation" in line:
			continue

		if "Methods inherited" in line:
			continue

		if "Overloaded function." in line:
			continue

		if "Method resolution order" in line:
			skipping = True

		if "Methods defined here" in line:
			skipping = False
			continue

		if "Data and other attributes defi" in line:
			continue

		if "Data descriptors defined" in line:
			continue

		if "-----------------------------" in line:
			continue

		if re.match(r"__\w+", line):
			skip_next = True
			continue

		if skipping:
			continue

		if re.match(r'\w+\(\.\.\.\)', line):
			next_mark = True
			continue

		if "class" in line:
			line = line.replace("()", "")

		if re.match(r"\d\. .+", line):
			line = re.sub(r"\d\. ", "", line)
			line.strip()
			next_mark = True

		if "for(int" in line:
			print(line)

		if next_mark or (re.match(r'\w+\(.*\)', line) and not any([line for pattern in pattens_to_skip if(pattern in line)])):
		#  (not "R90 " in line) and (not "M(e,e)" in line)) and (not "for(int" in line) and (not "if(" in line) and (not "assert(" in line) and (not "E(e,1))" in line) and (not " F(f, :) " in line) and (not "cur_energy(OPTIONAL)" in line) and (not "d(A, B) = max(" in line):
			next_mark = False
			line = "**`" + line + "`**"

		if "class " in line:
			line = line.replace(package + " = ", "")




		tmp += line + "\n\n"

	docs += tmp + "\n\n\n"
	# break


index = docs.find("FUNCTIONS")
docs = docs[index+10:]

index = docs.find("igl/helpers.py")
index = docs.find("\n\n**", index)
docs = docs[index:]

docs = docs.replace("2/3", "2 / 3")
docs = docs.replace("3/4", "3 / 4")

docs = docs.replace(" -> handle", "")
docs = docs.replace(" -> object", "")
docs = re.sub(r" -> Tuple\[.*\]", "", docs)
docs = docs.replace("numpy.dtype  str  type", "dtype")
docs = docs.replace(
	"std::__1::vector<std::__1::vector<int, std::__1::allocator<int> >, std::__1::allocator<std::__1::vector<int, std::__1::allocator<int> > > >", "vector<vector<int>>")
docs = docs.replace(
	"std::__1::function<double (Eigen::Matrix<double, -1, -1, 0, -1, -1>)>", "lambda function")

docs = docs.replace("scipy.sparse.csr_matrix  scipy.sparse.csc_matrix", "sparse_matrix")

tmp = docs

data = None
key = None

docs = ""
for line in iter(tmp.splitlines()):
	line = line.strip()
	if len(line) <= 0:
		continue
	if line.startswith("----"):
		continue
	if re.match(r'.+\(\.\.\.\)', line):
		continue

	if "class" in line:
		if data:
			format_data(data)
			data = None
		docs += "\n" + line +"\n"
		continue

	if line.startswith("**`"):
		if data:
			format_data(data)

		data = None
		title = line.replace("**`", "")
		title = title[:title.find("(")]
		docs += "### " + title + "\n"
		docs += line + "\n\n"
		continue

	if line == "Parameters" or line == "Returns" or line == "See also" or line == "Notes" or line == "Examples":
		key = line
		if data is None:
			data = {}
		data[key] = ""
		continue

	if data is None:
		docs += line + "\n"
		continue

	data[key] += line + "\n"




docs = docs.replace("class ", "## class ")

docs = "## Functions\n" + docs

with open("igl_docs.md", "w") as f:
	f.write(docs)
