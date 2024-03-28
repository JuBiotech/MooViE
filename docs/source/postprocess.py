import pathlib
import re
import sys
import textwrap
import urllib

#from utils import SUBMODULE_TO_PROJECT


def fix_videotags(dp: str):
    """Fixes HTML5 video tags to have 100 % width and show controls."""
    dp = pathlib.Path(dp)
    items = tuple(dp.glob("**/*.html"))
    for f, fp in enumerate(items):
        print(f"Fixing videotags... [{f+1}/{len(items)}] {fp}", end="\r")
        lines = [
            line.replace("<video ", "<video style=\"width:100%\" controls ")
            for line in fp.open("r", encoding="utf-8").readlines()
        ]
        with fp.open("w", encoding="utf-8") as file:
            file.writelines(lines)
    print()
    return



if __name__ == "__main__":
    fix_videotags(sys.argv[1])
    print("\n")
