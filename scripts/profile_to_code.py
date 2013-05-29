# -*- coding: utf-8 -*-
'''support only Python3 :)
特に何も考えずにバイナリにパックして辞書化
(バイト数(1 byte)、n-gram文字列)
格納数(1 byte) (言語へのidx(1 byte)、値(8 byte)) * 値が0じゃない言語
...

'''

import sys
import os
import string
import json
import struct


def main():
    profile_dir = sys.argv[1]
    profiles = []
    for fname in os.listdir(profile_dir):
        path = os.path.join(profile_dir, fname)
        if os.path.isfile(path):
            j = json.load(open(path))
            profiles.append(j)
    # {word: [prob, prob, prob, ...]}
    d = {}
    langlist = []
    for prof in profiles:
        for ngram, freq in prof['freq'].items():
            d.setdefault(ngram, [0] * len(profiles))[len(langlist)] = freq / prof['n_words'][len(ngram) - 1]
        langlist.append(prof['name'])
    # output files
    obj = bytearray()
    for ngram, freqs in d.items():
        b_ngram = b''.join(struct.pack('<I', ord(x)) for x in ngram)
        obj += struct.pack('B', len(b_ngram))
        obj += b_ngram
        b_freqs = bytearray()
        num_freq = 0
        for idx, freq in enumerate(freqs):
            if freq > 0:
                num_freq += 1
                b_freqs += struct.pack('B', idx)
                b_freqs += struct.pack('<d', freq)
        obj += struct.pack('B', num_freq)
        obj += b_freqs
    s = ''.join('\\x{:x}'.format(x) for x in obj)
    template = '''
#include "./ngram_storage.h"
#include <string>
namespace langdetect {
    std::string const NgramStorage::langdata_("$langlist");
    std::string const NgramStorage::ngramdata_("$ngramdata", $datasize);
}
'''
    print(string.Template(template).substitute(langlist=' '.join(langlist), ngramdata=s, datasize=len(obj)))


if __name__ == '__main__':
    main()
