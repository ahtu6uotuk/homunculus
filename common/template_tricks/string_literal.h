#pragma once

#include <type_traits>
#include <utility>

#define MAX_STRING_LITERAL_LENGTH 101
#define STRING_LITERAL(str) string_literal<char_pack<STRING_LITERAL_101(str)>>::s

#define STRING_LITERAL_101(str) STRING_LITERAL_100(str), ((TERMINATED_100(str))?(str[100]):('\0'))
#define STRING_LITERAL_100(str) STRING_LITERAL_99(str), ((TERMINATED_99(str))?(str[99]):('\0'))
#define STRING_LITERAL_99(str) STRING_LITERAL_98(str), ((TERMINATED_98(str))?(str[98]):('\0'))
#define STRING_LITERAL_98(str) STRING_LITERAL_97(str), ((TERMINATED_97(str))?(str[97]):('\0'))
#define STRING_LITERAL_97(str) STRING_LITERAL_96(str), ((TERMINATED_96(str))?(str[96]):('\0'))
#define STRING_LITERAL_96(str) STRING_LITERAL_95(str), ((TERMINATED_95(str))?(str[95]):('\0'))
#define STRING_LITERAL_95(str) STRING_LITERAL_94(str), ((TERMINATED_94(str))?(str[94]):('\0'))
#define STRING_LITERAL_94(str) STRING_LITERAL_93(str), ((TERMINATED_93(str))?(str[93]):('\0'))
#define STRING_LITERAL_93(str) STRING_LITERAL_92(str), ((TERMINATED_92(str))?(str[92]):('\0'))
#define STRING_LITERAL_92(str) STRING_LITERAL_91(str), ((TERMINATED_91(str))?(str[91]):('\0'))
#define STRING_LITERAL_91(str) STRING_LITERAL_90(str), ((TERMINATED_90(str))?(str[90]):('\0'))
#define STRING_LITERAL_90(str) STRING_LITERAL_89(str), ((TERMINATED_89(str))?(str[89]):('\0'))
#define STRING_LITERAL_89(str) STRING_LITERAL_88(str), ((TERMINATED_88(str))?(str[88]):('\0'))
#define STRING_LITERAL_88(str) STRING_LITERAL_87(str), ((TERMINATED_87(str))?(str[87]):('\0'))
#define STRING_LITERAL_87(str) STRING_LITERAL_86(str), ((TERMINATED_86(str))?(str[86]):('\0'))
#define STRING_LITERAL_86(str) STRING_LITERAL_85(str), ((TERMINATED_85(str))?(str[85]):('\0'))
#define STRING_LITERAL_85(str) STRING_LITERAL_84(str), ((TERMINATED_84(str))?(str[84]):('\0'))
#define STRING_LITERAL_84(str) STRING_LITERAL_83(str), ((TERMINATED_83(str))?(str[83]):('\0'))
#define STRING_LITERAL_83(str) STRING_LITERAL_82(str), ((TERMINATED_82(str))?(str[82]):('\0'))
#define STRING_LITERAL_82(str) STRING_LITERAL_81(str), ((TERMINATED_81(str))?(str[81]):('\0'))
#define STRING_LITERAL_81(str) STRING_LITERAL_80(str), ((TERMINATED_80(str))?(str[80]):('\0'))
#define STRING_LITERAL_80(str) STRING_LITERAL_79(str), ((TERMINATED_79(str))?(str[79]):('\0'))
#define STRING_LITERAL_79(str) STRING_LITERAL_78(str), ((TERMINATED_78(str))?(str[78]):('\0'))
#define STRING_LITERAL_78(str) STRING_LITERAL_77(str), ((TERMINATED_77(str))?(str[77]):('\0'))
#define STRING_LITERAL_77(str) STRING_LITERAL_76(str), ((TERMINATED_76(str))?(str[76]):('\0'))
#define STRING_LITERAL_76(str) STRING_LITERAL_75(str), ((TERMINATED_75(str))?(str[75]):('\0'))
#define STRING_LITERAL_75(str) STRING_LITERAL_74(str), ((TERMINATED_74(str))?(str[74]):('\0'))
#define STRING_LITERAL_74(str) STRING_LITERAL_73(str), ((TERMINATED_73(str))?(str[73]):('\0'))
#define STRING_LITERAL_73(str) STRING_LITERAL_72(str), ((TERMINATED_72(str))?(str[72]):('\0'))
#define STRING_LITERAL_72(str) STRING_LITERAL_71(str), ((TERMINATED_71(str))?(str[71]):('\0'))
#define STRING_LITERAL_71(str) STRING_LITERAL_70(str), ((TERMINATED_70(str))?(str[70]):('\0'))
#define STRING_LITERAL_70(str) STRING_LITERAL_69(str), ((TERMINATED_69(str))?(str[69]):('\0'))
#define STRING_LITERAL_69(str) STRING_LITERAL_68(str), ((TERMINATED_68(str))?(str[68]):('\0'))
#define STRING_LITERAL_68(str) STRING_LITERAL_67(str), ((TERMINATED_67(str))?(str[67]):('\0'))
#define STRING_LITERAL_67(str) STRING_LITERAL_66(str), ((TERMINATED_66(str))?(str[66]):('\0'))
#define STRING_LITERAL_66(str) STRING_LITERAL_65(str), ((TERMINATED_65(str))?(str[65]):('\0'))
#define STRING_LITERAL_65(str) STRING_LITERAL_64(str), ((TERMINATED_64(str))?(str[64]):('\0'))
#define STRING_LITERAL_64(str) STRING_LITERAL_63(str), ((TERMINATED_63(str))?(str[63]):('\0'))
#define STRING_LITERAL_63(str) STRING_LITERAL_62(str), ((TERMINATED_62(str))?(str[62]):('\0'))
#define STRING_LITERAL_62(str) STRING_LITERAL_61(str), ((TERMINATED_61(str))?(str[61]):('\0'))
#define STRING_LITERAL_61(str) STRING_LITERAL_60(str), ((TERMINATED_60(str))?(str[60]):('\0'))
#define STRING_LITERAL_60(str) STRING_LITERAL_59(str), ((TERMINATED_59(str))?(str[59]):('\0'))
#define STRING_LITERAL_59(str) STRING_LITERAL_58(str), ((TERMINATED_58(str))?(str[58]):('\0'))
#define STRING_LITERAL_58(str) STRING_LITERAL_57(str), ((TERMINATED_57(str))?(str[57]):('\0'))
#define STRING_LITERAL_57(str) STRING_LITERAL_56(str), ((TERMINATED_56(str))?(str[56]):('\0'))
#define STRING_LITERAL_56(str) STRING_LITERAL_55(str), ((TERMINATED_55(str))?(str[55]):('\0'))
#define STRING_LITERAL_55(str) STRING_LITERAL_54(str), ((TERMINATED_54(str))?(str[54]):('\0'))
#define STRING_LITERAL_54(str) STRING_LITERAL_53(str), ((TERMINATED_53(str))?(str[53]):('\0'))
#define STRING_LITERAL_53(str) STRING_LITERAL_52(str), ((TERMINATED_52(str))?(str[52]):('\0'))
#define STRING_LITERAL_52(str) STRING_LITERAL_51(str), ((TERMINATED_51(str))?(str[51]):('\0'))
#define STRING_LITERAL_51(str) STRING_LITERAL_50(str), ((TERMINATED_50(str))?(str[50]):('\0'))
#define STRING_LITERAL_50(str) STRING_LITERAL_49(str), ((TERMINATED_49(str))?(str[49]):('\0'))
#define STRING_LITERAL_49(str) STRING_LITERAL_48(str), ((TERMINATED_48(str))?(str[48]):('\0'))
#define STRING_LITERAL_48(str) STRING_LITERAL_47(str), ((TERMINATED_47(str))?(str[47]):('\0'))
#define STRING_LITERAL_47(str) STRING_LITERAL_46(str), ((TERMINATED_46(str))?(str[46]):('\0'))
#define STRING_LITERAL_46(str) STRING_LITERAL_45(str), ((TERMINATED_45(str))?(str[45]):('\0'))
#define STRING_LITERAL_45(str) STRING_LITERAL_44(str), ((TERMINATED_44(str))?(str[44]):('\0'))
#define STRING_LITERAL_44(str) STRING_LITERAL_43(str), ((TERMINATED_43(str))?(str[43]):('\0'))
#define STRING_LITERAL_43(str) STRING_LITERAL_42(str), ((TERMINATED_42(str))?(str[42]):('\0'))
#define STRING_LITERAL_42(str) STRING_LITERAL_41(str), ((TERMINATED_41(str))?(str[41]):('\0'))
#define STRING_LITERAL_41(str) STRING_LITERAL_40(str), ((TERMINATED_40(str))?(str[40]):('\0'))
#define STRING_LITERAL_40(str) STRING_LITERAL_39(str), ((TERMINATED_39(str))?(str[39]):('\0'))
#define STRING_LITERAL_39(str) STRING_LITERAL_38(str), ((TERMINATED_38(str))?(str[38]):('\0'))
#define STRING_LITERAL_38(str) STRING_LITERAL_37(str), ((TERMINATED_37(str))?(str[37]):('\0'))
#define STRING_LITERAL_37(str) STRING_LITERAL_36(str), ((TERMINATED_36(str))?(str[36]):('\0'))
#define STRING_LITERAL_36(str) STRING_LITERAL_35(str), ((TERMINATED_35(str))?(str[35]):('\0'))
#define STRING_LITERAL_35(str) STRING_LITERAL_34(str), ((TERMINATED_34(str))?(str[34]):('\0'))
#define STRING_LITERAL_34(str) STRING_LITERAL_33(str), ((TERMINATED_33(str))?(str[33]):('\0'))
#define STRING_LITERAL_33(str) STRING_LITERAL_32(str), ((TERMINATED_32(str))?(str[32]):('\0'))
#define STRING_LITERAL_32(str) STRING_LITERAL_31(str), ((TERMINATED_31(str))?(str[31]):('\0'))
#define STRING_LITERAL_31(str) STRING_LITERAL_30(str), ((TERMINATED_30(str))?(str[30]):('\0'))
#define STRING_LITERAL_30(str) STRING_LITERAL_29(str), ((TERMINATED_29(str))?(str[29]):('\0'))
#define STRING_LITERAL_29(str) STRING_LITERAL_28(str), ((TERMINATED_28(str))?(str[28]):('\0'))
#define STRING_LITERAL_28(str) STRING_LITERAL_27(str), ((TERMINATED_27(str))?(str[27]):('\0'))
#define STRING_LITERAL_27(str) STRING_LITERAL_26(str), ((TERMINATED_26(str))?(str[26]):('\0'))
#define STRING_LITERAL_26(str) STRING_LITERAL_25(str), ((TERMINATED_25(str))?(str[25]):('\0'))
#define STRING_LITERAL_25(str) STRING_LITERAL_24(str), ((TERMINATED_24(str))?(str[24]):('\0'))
#define STRING_LITERAL_24(str) STRING_LITERAL_23(str), ((TERMINATED_23(str))?(str[23]):('\0'))
#define STRING_LITERAL_23(str) STRING_LITERAL_22(str), ((TERMINATED_22(str))?(str[22]):('\0'))
#define STRING_LITERAL_22(str) STRING_LITERAL_21(str), ((TERMINATED_21(str))?(str[21]):('\0'))
#define STRING_LITERAL_21(str) STRING_LITERAL_20(str), ((TERMINATED_20(str))?(str[20]):('\0'))
#define STRING_LITERAL_20(str) STRING_LITERAL_19(str), ((TERMINATED_19(str))?(str[19]):('\0'))
#define STRING_LITERAL_19(str) STRING_LITERAL_18(str), ((TERMINATED_18(str))?(str[18]):('\0'))
#define STRING_LITERAL_18(str) STRING_LITERAL_17(str), ((TERMINATED_17(str))?(str[17]):('\0'))
#define STRING_LITERAL_17(str) STRING_LITERAL_16(str), ((TERMINATED_16(str))?(str[16]):('\0'))
#define STRING_LITERAL_16(str) STRING_LITERAL_15(str), ((TERMINATED_15(str))?(str[15]):('\0'))
#define STRING_LITERAL_15(str) STRING_LITERAL_14(str), ((TERMINATED_14(str))?(str[14]):('\0'))
#define STRING_LITERAL_14(str) STRING_LITERAL_13(str), ((TERMINATED_13(str))?(str[13]):('\0'))
#define STRING_LITERAL_13(str) STRING_LITERAL_12(str), ((TERMINATED_12(str))?(str[12]):('\0'))
#define STRING_LITERAL_12(str) STRING_LITERAL_11(str), ((TERMINATED_11(str))?(str[11]):('\0'))
#define STRING_LITERAL_11(str) STRING_LITERAL_10(str), ((TERMINATED_10(str))?(str[10]):('\0'))
#define STRING_LITERAL_10(str) STRING_LITERAL_9(str), ((TERMINATED_9(str))?(str[9]):('\0'))
#define STRING_LITERAL_9(str) STRING_LITERAL_8(str), ((TERMINATED_8(str))?(str[8]):('\0'))
#define STRING_LITERAL_8(str) STRING_LITERAL_7(str), ((TERMINATED_7(str))?(str[7]):('\0'))
#define STRING_LITERAL_7(str) STRING_LITERAL_6(str), ((TERMINATED_6(str))?(str[6]):('\0'))
#define STRING_LITERAL_6(str) STRING_LITERAL_5(str), ((TERMINATED_5(str))?(str[5]):('\0'))
#define STRING_LITERAL_5(str) STRING_LITERAL_4(str), ((TERMINATED_4(str))?(str[4]):('\0'))
#define STRING_LITERAL_4(str) STRING_LITERAL_3(str), ((TERMINATED_3(str))?(str[3]):('\0'))
#define STRING_LITERAL_3(str) STRING_LITERAL_2(str), ((TERMINATED_2(str))?(str[2]):('\0'))
#define STRING_LITERAL_2(str) STRING_LITERAL_1(str), ((TERMINATED_1(str))?(str[1]):('\0'))
#define STRING_LITERAL_1(str) str[0]


#define TERMINATED_100(str) TERMINATED_99(str) && str[99]
#define TERMINATED_99(str) TERMINATED_98(str) && str[98]
#define TERMINATED_98(str) TERMINATED_97(str) && str[97]
#define TERMINATED_97(str) TERMINATED_96(str) && str[96]
#define TERMINATED_96(str) TERMINATED_95(str) && str[95]
#define TERMINATED_95(str) TERMINATED_94(str) && str[94]
#define TERMINATED_94(str) TERMINATED_93(str) && str[93]
#define TERMINATED_93(str) TERMINATED_92(str) && str[92]
#define TERMINATED_92(str) TERMINATED_91(str) && str[91]
#define TERMINATED_91(str) TERMINATED_90(str) && str[90]
#define TERMINATED_90(str) TERMINATED_89(str) && str[89]
#define TERMINATED_89(str) TERMINATED_88(str) && str[88]
#define TERMINATED_88(str) TERMINATED_87(str) && str[87]
#define TERMINATED_87(str) TERMINATED_86(str) && str[86]
#define TERMINATED_86(str) TERMINATED_85(str) && str[85]
#define TERMINATED_85(str) TERMINATED_84(str) && str[84]
#define TERMINATED_84(str) TERMINATED_83(str) && str[83]
#define TERMINATED_83(str) TERMINATED_82(str) && str[82]
#define TERMINATED_82(str) TERMINATED_81(str) && str[81]
#define TERMINATED_81(str) TERMINATED_80(str) && str[80]
#define TERMINATED_80(str) TERMINATED_79(str) && str[79]
#define TERMINATED_79(str) TERMINATED_78(str) && str[78]
#define TERMINATED_78(str) TERMINATED_77(str) && str[77]
#define TERMINATED_77(str) TERMINATED_76(str) && str[76]
#define TERMINATED_76(str) TERMINATED_75(str) && str[75]
#define TERMINATED_75(str) TERMINATED_74(str) && str[74]
#define TERMINATED_74(str) TERMINATED_73(str) && str[73]
#define TERMINATED_73(str) TERMINATED_72(str) && str[72]
#define TERMINATED_72(str) TERMINATED_71(str) && str[71]
#define TERMINATED_71(str) TERMINATED_70(str) && str[70]
#define TERMINATED_70(str) TERMINATED_69(str) && str[69]
#define TERMINATED_69(str) TERMINATED_68(str) && str[68]
#define TERMINATED_68(str) TERMINATED_67(str) && str[67]
#define TERMINATED_67(str) TERMINATED_66(str) && str[66]
#define TERMINATED_66(str) TERMINATED_65(str) && str[65]
#define TERMINATED_65(str) TERMINATED_64(str) && str[64]
#define TERMINATED_64(str) TERMINATED_63(str) && str[63]
#define TERMINATED_63(str) TERMINATED_62(str) && str[62]
#define TERMINATED_62(str) TERMINATED_61(str) && str[61]
#define TERMINATED_61(str) TERMINATED_60(str) && str[60]
#define TERMINATED_60(str) TERMINATED_59(str) && str[59]
#define TERMINATED_59(str) TERMINATED_58(str) && str[58]
#define TERMINATED_58(str) TERMINATED_57(str) && str[57]
#define TERMINATED_57(str) TERMINATED_56(str) && str[56]
#define TERMINATED_56(str) TERMINATED_55(str) && str[55]
#define TERMINATED_55(str) TERMINATED_54(str) && str[54]
#define TERMINATED_54(str) TERMINATED_53(str) && str[53]
#define TERMINATED_53(str) TERMINATED_52(str) && str[52]
#define TERMINATED_52(str) TERMINATED_51(str) && str[51]
#define TERMINATED_51(str) TERMINATED_50(str) && str[50]
#define TERMINATED_50(str) TERMINATED_49(str) && str[49]
#define TERMINATED_49(str) TERMINATED_48(str) && str[48]
#define TERMINATED_48(str) TERMINATED_47(str) && str[47]
#define TERMINATED_47(str) TERMINATED_46(str) && str[46]
#define TERMINATED_46(str) TERMINATED_45(str) && str[45]
#define TERMINATED_45(str) TERMINATED_44(str) && str[44]
#define TERMINATED_44(str) TERMINATED_43(str) && str[43]
#define TERMINATED_43(str) TERMINATED_42(str) && str[42]
#define TERMINATED_42(str) TERMINATED_41(str) && str[41]
#define TERMINATED_41(str) TERMINATED_40(str) && str[40]
#define TERMINATED_40(str) TERMINATED_39(str) && str[39]
#define TERMINATED_39(str) TERMINATED_38(str) && str[38]
#define TERMINATED_38(str) TERMINATED_37(str) && str[37]
#define TERMINATED_37(str) TERMINATED_36(str) && str[36]
#define TERMINATED_36(str) TERMINATED_35(str) && str[35]
#define TERMINATED_35(str) TERMINATED_34(str) && str[34]
#define TERMINATED_34(str) TERMINATED_33(str) && str[33]
#define TERMINATED_33(str) TERMINATED_32(str) && str[32]
#define TERMINATED_32(str) TERMINATED_31(str) && str[31]
#define TERMINATED_31(str) TERMINATED_30(str) && str[30]
#define TERMINATED_30(str) TERMINATED_29(str) && str[29]
#define TERMINATED_29(str) TERMINATED_28(str) && str[28]
#define TERMINATED_28(str) TERMINATED_27(str) && str[27]
#define TERMINATED_27(str) TERMINATED_26(str) && str[26]
#define TERMINATED_26(str) TERMINATED_25(str) && str[25]
#define TERMINATED_25(str) TERMINATED_24(str) && str[24]
#define TERMINATED_24(str) TERMINATED_23(str) && str[23]
#define TERMINATED_23(str) TERMINATED_22(str) && str[22]
#define TERMINATED_22(str) TERMINATED_21(str) && str[21]
#define TERMINATED_21(str) TERMINATED_20(str) && str[20]
#define TERMINATED_20(str) TERMINATED_19(str) && str[19]
#define TERMINATED_19(str) TERMINATED_18(str) && str[18]
#define TERMINATED_18(str) TERMINATED_17(str) && str[17]
#define TERMINATED_17(str) TERMINATED_16(str) && str[16]
#define TERMINATED_16(str) TERMINATED_15(str) && str[15]
#define TERMINATED_15(str) TERMINATED_14(str) && str[14]
#define TERMINATED_14(str) TERMINATED_13(str) && str[13]
#define TERMINATED_13(str) TERMINATED_12(str) && str[12]
#define TERMINATED_12(str) TERMINATED_11(str) && str[11]
#define TERMINATED_11(str) TERMINATED_10(str) && str[10]
#define TERMINATED_10(str) TERMINATED_9(str) && str[9]
#define TERMINATED_9(str) TERMINATED_8(str) && str[8]
#define TERMINATED_8(str) TERMINATED_7(str) && str[7]
#define TERMINATED_7(str) TERMINATED_6(str) && str[6]
#define TERMINATED_6(str) TERMINATED_5(str) && str[5]
#define TERMINATED_5(str) TERMINATED_4(str) && str[4]
#define TERMINATED_4(str) TERMINATED_3(str) && str[3]
#define TERMINATED_3(str) TERMINATED_2(str) && str[2]
#define TERMINATED_2(str) TERMINATED_1(str) && str[1]
#define TERMINATED_1(str) str[0]

template <char... Cs>
struct char_pack {
  static constexpr char const arr[sizeof...(Cs) + 1] = {Cs..., 0};
  static constexpr std::size_t non_zero_count = (((Cs != 0)?1:0) + ...);
  static_assert(non_zero_count < MAX_STRING_LITERAL_LENGTH, "You need to create more macros");
};

template <char... Cs>
constexpr char const char_pack<Cs...>::arr[sizeof...(Cs) + 1];

template <char... Cs>
constexpr std::size_t char_pack<Cs...>::non_zero_count;

template <class CP, class = void, class = std::make_index_sequence<CP::non_zero_count>>
struct string_literal;

template <char... Cs, std::size_t... Is>
struct string_literal<char_pack<Cs...>, std::enable_if_t<(Cs && ...)>, std::index_sequence<Is...>> {
  static constexpr char const s[sizeof...(Cs) + 1] = {Cs..., '\0'};
};

template <char... Cs, std::size_t... Is>
constexpr char const string_literal<char_pack<Cs...>, std::enable_if_t<(Cs && ...)>, std::index_sequence<Is...>>::s[sizeof...(Cs) + 1];

template <char... Cs, std::size_t... Is>
struct string_literal<char_pack<Cs...>, std::enable_if_t<!(Cs && ...)>, std::index_sequence<Is...>>: string_literal<char_pack<char_pack<Cs...>::arr[Is]...>> { };
