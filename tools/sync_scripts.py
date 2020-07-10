#!/usr/bin/env python3

import os
import shutil

def main():
    prefix = '..'
    if os.path.exists('tools'):
        prefix = '.'

    p = prefix + '/bin/ray/Debug/scripts'
    if os.path.exists(p):
        shutil.rmtree(p)
        shutil.copytree(prefix + '/ray/scripts', p)

if __name__ == "__main__":
    main()