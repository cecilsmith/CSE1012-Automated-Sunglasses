# This tool converts .stl files into ASCII format. This is readable by GitHub's README.

import stl
from stl import mesh

your_mesh = mesh.Mesh.from_file('./CAD/ServoMountV1.stl')
your_mesh.save('./CAD/outputObject.stl', mode=stl.Mode.ASCII)
