from skbuild import setup

install_requires = [
    "numpy",
]

setup(
    name="pysdf2d",
    version="0.0.1",
    description="2d sdf generator",
    author="Hirokazu Ishida",
    license="MIT",
    packages=["pysdf2d"],
    package_dir={"": "python"},
    cmake_install_dir="python/pysdf2d/",
    install_requires=install_requires,
    package_data={"pysdf2d": ["py.typed", "*.pyi"]},
)
