import re

class NameConvertor:
    def __init__(self, name):
        if re.match('([A-Z][a-z0-9]*)+', name):
            self.__from_AaBbCc(name)
        elif re.match('[a-z0-9]+([A-Z][a-z0-9]*)*', name):
            self.__from_aaBbCc(name)
        elif re.match('([A-Za-z0-9]+_)*[A-Za-z0-9]+|[A-Za-z0-9]+', name):
            self.__from_aa_bb_cc(name)
        else:
            raise 'can not parse {0}'.format(name)

        self.__uniform_word_list()

    def __from_AaBbCc(self, name):
        self.word_list = re.findall('[A-Z][a-z0-9]*', name)

    def __from_aaBbCc(self, name):
        self.word_list = re.findall('[A-Z][a-z0-9]*|[a-z0-9]+', name)

    def __from_aa_bb_cc(self, name):
        self.word_list = re.findall('[A-Z][a-z0-9]*|[a-z0-9]+', name)

    def __uniform_word_list(self):
        for i in range(0, len(self.word_list)):
            self.word_list[i] = self.word_list[i].lower()

    def to_AaBbCc(self):
        dst_str = str()
        for w in self.word_list:
            dst_str = dst_str + w.title()
        return dst_str

    def to_aaBbCc(self):
        dst_str = str()
        for i in range(0, len(self.word_list)):
            if i == 0:
                dst_str = self.word_list[0]
            else:
                dst_str = dst_str + self.word_list[i].title()
        return dst_str
    
    def to_aa_bb_cc(self):
        dst_str = str()
        for i in range(0, len(self.word_list)):
            if i == 0:
                dst_str = self.word_list[0]
            else:
                dst_str = dst_str + '_' + self.word_list[i]
        return dst_str

    def to_AA_BB_CC(self):
        dst_str = str()
        for i in range(0, len(self.word_list)):
            if i == 0:
                dst_str = self.word_list[0].upper()
            else:
                dst_str = dst_str + '_' + self.word_list[i].upper()
        return dst_str

    def to_aabbcc(self):
        dst_str = str()
        for w in self.word_list:
            dst_str = dst_str + w
        return dst_str

    def to_AABBCC(self):
        dst_str = str()
        for w in self.word_list:
            dst_str = dst_str + w.upper()
        return dst_str

    def to_AA_BB_CC_H(self):
        return self.to_AA_BB_CC() + '_H'

    def to__AA_BB_CC_H(self):
        return '_' + self.to_AA_BB_CC_H()

    def to__AA_BB_CC_H_(self):
        return self.to__AA_BB_CC_H() + '_'

# convertor = NameConvertor('LicenseManagerModule')
# print(convertor.to_AaBbCc())
# print(convertor.to_aaBbCc())
# print(convertor.to_aabbcc())
# print(convertor.to_AABBCC())
# print(convertor.to_AA_BB_CC_H())
# print(convertor.to_AA_BB_CC())
# print(convertor.to_aa_bb_cc())
# print(convertor.to__AA_BB_CC_H_())
# print(convertor.to__AA_BB_CC_H())