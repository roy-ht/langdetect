# -*- coding: utf-8 -*-
''' messages.propertiesからNgram.KANJI_*_*を取得して変換mapを作る
'''
import sys
import string
import re


def main():
    spath = sys.argv[1]
    template = string.Template(u'''{
    $maps
}
''')
    maps = []
    for line in open(spath):
        line = line.strip()
        if not line.startswith('NGram.KANJI_'):
            continue
        codestr = line.split('=', 1)[1]
        codes = ['0x' + x[2:] for x in re.findall(r'\\u[0-9a-fA-F]+', codestr)]
        cstr = ', '.join('{{{0}, {1}}}'.format(codes[0], x) for x in codes[1:])
        maps.append(cstr)
    print(template.substitute(maps=',\n'.join(maps)))

if __name__ == '__main__':
    main()
