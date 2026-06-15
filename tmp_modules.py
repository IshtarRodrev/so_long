import importlib.util
mods = ['cairosvg','svgpathtools','PIL','matplotlib','numpy']
for m in mods:
    print(m, importlib.util.find_spec(m))
