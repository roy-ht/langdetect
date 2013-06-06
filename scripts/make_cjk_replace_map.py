# -*- coding: utf-8 -*-
''' messages.propertiesからNgram.KANJI_*_*を取得して変換mapを作る
'''
import sys
import string
import re


def main():
    spath = sys.argv[1]
    template = string.Template(u'''{$tgts}
{$sources}
''')
    maps = []
    for line in open(spath):
        line = line.strip()
        if not line.startswith('NGram.KANJI_'):
            continue
        codestr = line.split('=', 1)[1]
        codes = ['0x' + x[2:] for x in re.findall(r'\\u[0-9a-fA-F]+', codestr)]
        maps.append(codes)
    tgtstr = ','.join(x[0] for x in maps)
    sourcestr = ',\n'.join('{' + ','.join(x[1:]) + '}' for x in maps)
    print(template.substitute(tgts=tgtstr, sources=sourcestr))

if __name__ == '__main__':
    main()
