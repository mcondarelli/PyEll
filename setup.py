from setuptools import setup, find_packages

setup(
    name="ell-pkg-mcon",
    version="0.0.1",
    author="Mauro Condarelli",
    author_email="mc5686@mclink.it",
    description="Python3 bindings for Ell lib",
    packages=find_packages(),
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["ell_build.py:ffibuilder"],  # "filename:global"
    install_requires=["cffi>=1.0.0"],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Linux",
    ],
    python_requires='>=3.6',
)
