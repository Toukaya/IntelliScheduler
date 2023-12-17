//
// Created by Touka on 2023/12/17.
//

#ifndef ENUMUTILS_H
#define ENUMUTILS_H
#include "types.hpp"

namespace touka {
    class EnumUtils {
    public:
        template<typename T>
        static constexpr auto toUnderlying(T t) noexcept {
            return static_cast<std::underlying_type_t<T>>(t);
        }

        template <typename EnumType>
        static String enumToString(EnumType enumValue, const std::map<EnumType, std::string>& enumToStrMap) {
            try {
                return String::fromStdString(enumToStrMap.at(enumValue));
            } catch (std::out_of_range&) {
                throw std::invalid_argument("Invalid enum value");
            }
        }

        template <typename EnumType>
        static EnumType stringToEnum(const String& enumStr, const std::map<EnumType, std::string>& enumToStrMap) {
            for (const auto& [enumValue, enumStrValue] : enumToStrMap)
                if (enumStrValue == enumStr)
                    return enumValue;
            throw std::invalid_argument("Invalid enum string");
        }
    };
}

#endif //ENUMUTILS_H
