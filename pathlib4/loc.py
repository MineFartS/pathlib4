from .Path import Path
from ._loc import _loc
from os import makedirs

temp: Path
script: Path
cache: Path

_i_loc = _loc()

def __getattr__(name:str):
    path = getattr(_i_loc, name)
    makedirs(path, exist_ok=True)
    return Path(path)

