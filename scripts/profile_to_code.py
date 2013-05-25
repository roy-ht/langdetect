# -*- coding: utf-8 -*-
'''support only Python3 :)'''

import sys
import string
import os
import json


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
    #output files
    template = '''// coding: utf-8
// This file was automatically created.
#include <vector>
#include "./ngram_storage.h"
namespace langdetect {
    size_t const NgramStorage::langnum_ = $langsize;
    std::vector<std::string> NgramStorage::langlist_ = {$langlist};
    NgramStorage::ProbMap const NgramStorage::probmap_ = {
        $probmap
    }
}
'''
    langlist_s = ', '.join(langlist)
    probmap_s = ',\n'.join('{{"{0}", {{{1}}}}}'.format(x, ', '.join('0' if z == 0 else '{:.16e}'.format(z) for z in y)) for x, y in d.items())
    output = string.Template(template).substitute(langsize=len(langlist), langlist=langlist_s, probmap=probmap_s)
    sys.stdout.buffer.write(output.encode('utf-8'))


if __name__ == '__main__':
    main()
