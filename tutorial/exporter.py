import pydoc
import meshplot
import re
import queue
import tempfile

packages = queue.Queue()
packages.put("igl")

docs = ""



while not packages.empty():
	package = packages.get()

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
	lines = lines.replace("class ", "## class ")
	lines = lines.replace("self: polyfempy.polyfempy.Solver, ", "")
	lines = lines.replace("self: polyfempy.polyfempy.Solver", "")
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

		if re.match(r'\w+\(...\)', line):
			next_mark = True
			continue

		if "class" in line:
			line = line.replace("()", "")

		if re.match(r"\d\. .+", line):
			line = re.sub(r"\d\. ", "", line)
			line.strip()
			next_mark = True

		if next_mark or re.match(r'\w+\(.*\)', line):
			next_mark = False
			line = "**`" + line + "`**"

		if "## class " in line:
			line = line.replace(package + " = ", "")




		tmp += line + "\n\n"

	docs += tmp + "\n\n\n"
	# break

with open("igl_docs.md", "w") as f:
	f.write(docs)
