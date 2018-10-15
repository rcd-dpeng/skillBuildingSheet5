from distutils.core import setup

setup(
    name="pidev",
    version='0.1dev',
    packages=["pidev"],
    long_description="A DPEA package containing RPi infrastructure helpers.",
    install_requires=[
        "pyserial",
    ]
)
