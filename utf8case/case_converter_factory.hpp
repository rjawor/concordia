#ifndef CASE_CONVERTER_FACTORY_HDR
#define CASE_CONVERTER_FACTORY_HDR

#include <boost/shared_ptr.hpp>

#include "general_case_converter.hpp"
#include "concordia/concordia_exception.hpp"
#include "regular_contextual_case_converter.hpp"
#include "turkish_and_azeri_lower_contextual_case_converter.hpp"
#include "turkish_and_azeri_upper_contextual_case_converter.hpp"

const size_t NUMBER_OF_CASE_TYPES = 3;

template<typename octet_iterator, typename output_iterator>
class CaseConverterFactory {

private:
    enum {
        LOWER_INDEX = 0,
        UPPER_INDEX = 1,
        TITLE_INDEX = 2
    };

    boost::shared_ptr<RangeBasedCaseConverter> rangeBasedCaseConverters_[NUMBER_OF_CASE_TYPES];
    boost::shared_ptr<SpecialCasingConverter> specialCasingConverters_[NUMBER_OF_CASE_TYPES];

    boost::shared_ptr<ContextualCaseConverter> regularContextualCaseConverter_;
    boost::shared_ptr<ContextualCaseConverter> turkishAndAzeriUpperContextualCaseConverter_;
    boost::shared_ptr<ContextualCaseConverter> turkishAndAzeriLowerContextualCaseConverter_;

    class Exception : public ConcordiaException  {
    public:
        Exception(const std::string& msg): ConcordiaException(msg) {
        }

        virtual ~Exception() throw() {}
    };

    void checkRawConverters_(int case_index) {
        if (!rangeBasedCaseConverters_[case_index]) {
            boost::shared_ptr<RangeBasedCaseConverter> converter;

            switch (case_index) {
            case LOWER_INDEX: converter.reset(
                new RangeBasedCaseConverter(
                    LOWER_CASE_RANGES_SIZE,
                    LOWER_CASE_RANGES));
                break;
            case UPPER_INDEX: converter.reset(
                new RangeBasedCaseConverter(
                    UPPER_CASE_RANGES_SIZE,
                    UPPER_CASE_RANGES));
                break;
            case TITLE_INDEX: converter.reset(
                new RangeBasedCaseConverter(
                    TITLE_CASE_RANGES_SIZE,
                    TITLE_CASE_RANGES));
                break;
            default:
                throw Exception("????");
            }

            rangeBasedCaseConverters_[case_index] = converter;
        }

        if (!specialCasingConverters_[case_index]) {
            boost::shared_ptr<SpecialCasingConverter> converter;

            switch (case_index) {
            case LOWER_INDEX: converter.reset(
                new SpecialCasingConverter(
                    LOWER_SPECIAL_CASING_SIZE,
                    LOWER_SPECIAL_CASING));
                break;
            case UPPER_INDEX: converter.reset(
                new SpecialCasingConverter(
                    UPPER_SPECIAL_CASING_SIZE,
                    UPPER_SPECIAL_CASING));
                break;
            case TITLE_INDEX: converter.reset(
                new SpecialCasingConverter(
                    TITLE_SPECIAL_CASING_SIZE,
                    TITLE_SPECIAL_CASING));
                break;
            default:
                throw Exception("????");
            }

            specialCasingConverters_[case_index] = converter;
        }
    }

    boost::shared_ptr<GeneralCaseConverter<octet_iterator, output_iterator> > getCaseConverter_(
        int case_index, const std::string& language_code) {

        checkRawConverters_(case_index);

        return boost::shared_ptr<GeneralCaseConverter<octet_iterator, output_iterator> >(
            new GeneralCaseConverter<octet_iterator, output_iterator> (
                rangeBasedCaseConverters_[case_index],
                specialCasingConverters_[case_index],
                getContextualCaseConverterForLanguage_(language_code, case_index)));
    }

public:
    CaseConverterFactory():
        regularContextualCaseConverter_(
            boost::shared_ptr<ContextualCaseConverter>(new RegularContextualCaseConverter())),
        turkishAndAzeriUpperContextualCaseConverter_(
            boost::shared_ptr<ContextualCaseConverter>(
                new TurkishAndAzeriUpperContextualCaseConverter())),
        turkishAndAzeriLowerContextualCaseConverter_(
            boost::shared_ptr<ContextualCaseConverter>(
                new TurkishAndAzeriLowerContextualCaseConverter())) {
    }

    boost::shared_ptr<ContextualCaseConverter> getContextualCaseConverterForLanguage_(
        const std::string& languageCode, int caseIndex) {
        if (languageCode == "lt")
            throw Exception(std::string("language '") + languageCode
                            + "' is not handled yet in lower/upper/title-casing");

        if (languageCode == "tr" || languageCode == "az")
            return
                caseIndex == LOWER_INDEX
                ? turkishAndAzeriLowerContextualCaseConverter_
                : turkishAndAzeriUpperContextualCaseConverter_;

        return regularContextualCaseConverter_;
    }

    boost::shared_ptr<GeneralCaseConverter<octet_iterator, output_iterator> >
    getLowerCaseConverter(const std::string& language_code) {
        return getCaseConverter_(LOWER_INDEX, language_code);
    }

    boost::shared_ptr<GeneralCaseConverter<octet_iterator, output_iterator> >
    getUpperCaseConverter(const std::string& language_code) {
        return getCaseConverter_(UPPER_INDEX, language_code);
    }

    boost::shared_ptr<GeneralCaseConverter<octet_iterator, output_iterator> >
    getTitleCaseConverter(const std::string& language_code) {
        return getCaseConverter_(TITLE_INDEX, language_code);
    }

};

#endif
