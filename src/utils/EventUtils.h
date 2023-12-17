//
// Created by Touka on 2023/12/16.
//

#ifndef EVENTUTILS_H
#define EVENTUTILS_H
#include "types.hpp"

namespace touka {
    enum Priority {
        UNDEFINED = 0,
        HIGHEST = 1,
        HIGH = 2,
        ABOVE_NORMAL = 3,
        NORMAL = 4,
        BELOW_NORMAL = 5,
        LOW = 6,
        LOWEST = 7,
        RESERVED1 = 8,
        RESERVED2 = 9
    };

    enum class Classification {
        PUBLIC,
        PRIVATE,
        CONFIDENTIAL
    };

    enum class Status {
        TENTATIVE,
        CONFIRMED,
        CANCELLED
    };

    enum class Transparency {
        OPAQUE,
        TRANSPARENT
    };
class EventUtils {
public:

    static String priorityToString(Priority priority) {
        static const std::map<Priority, std::string> priorityToStrMap = {
            {Priority::HIGHEST, "HIGHEST"},
            {Priority::HIGH, "HIGH"},
            {Priority::ABOVE_NORMAL, "ABOVE-NORMAL"},
            {Priority::NORMAL, "NORMAL"},
            {Priority::BELOW_NORMAL, "BELOW-NORMAL"},
            {Priority::LOW, "LOW"},
            {Priority::LOWEST, "LOWEST"},
            {Priority::RESERVED1, "RESERVED1"},
            {Priority::RESERVED2, "RESERVED2"},
            {Priority::UNDEFINED, "UNDEFINED"}
        };

        return EnumUtils::enumToString(priority, priorityToStrMap);
    }

    static String classificationToString(Classification classification) {
        static const std::map<Classification, std::string> classificationToStrMap = {
            {Classification::PUBLIC, "PUBLIC"},
            {Classification::PRIVATE, "PRIVATE"},
            {Classification::CONFIDENTIAL, "CONFIDENTIAL"}
        };

        return EnumUtils::enumToString(classification, classificationToStrMap);
    }

    static String statusToString(Status status) {
        static const std::map<Status, std::string> statusToStrMap = {
            {Status::TENTATIVE, "TENTATIVE"},
            {Status::CONFIRMED, "CONFIRMED"},
            {Status::CANCELLED, "CANCELLED"}
        };

        return EnumUtils::enumToString(status, statusToStrMap);
    }

    static String transparencyToString(Transparency transparency) {
        static const std::map<Transparency, std::string> transparencyToStrMap = {
            {Transparency::OPAQUE, "OPAQUE"},
            {Transparency::TRANSPARENT, "TRANSPARENT"}
        };

        return EnumUtils::enumToString(transparency, transparencyToStrMap);
    }
    

    static Priority stringToPriority(const String& priority) {
        static const std::map<std::string, Priority> strToPriorityMap = {
            {"HIGHEST", Priority::HIGHEST},
            {"HIGH", Priority::HIGH},
            {"ABOVE-NORMAL", Priority::ABOVE_NORMAL},
            {"NORMAL", Priority::NORMAL},
            {"BELOW-NORMAL", Priority::BELOW_NORMAL},
            {"LOW", Priority::LOW},
            {"LOWEST", Priority::LOWEST},
            {"RESERVED1", Priority::RESERVED1},
            {"RESERVED2", Priority::RESERVED2},
            {"UNDEFINED", Priority::UNDEFINED}
        };

        std::string lowerStr(priority.toStdString());
        std::ranges::transform(lowerStr, lowerStr.begin(), ::tolower);

        auto it = strToPriorityMap.find(lowerStr);
        if (it != strToPriorityMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid priority string");
        }
    }

    static Classification stringToClassification(const String& classification) {
        static const std::map<std::string, Classification> strToClassificationMap = {
            {"PUBLIC", Classification::PUBLIC},
            {"PRIVATE", Classification::PRIVATE},
            {"CONFIDENTIAL", Classification::CONFIDENTIAL}
        };

        std::string lowerStr(classification.toStdString());
        std::ranges::transform(lowerStr, lowerStr.begin(), ::tolower);

        auto it = strToClassificationMap.find(lowerStr);
        if (it != strToClassificationMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid classification string");
        }
    }

    static Status stringToStatus(const String& status) {
        static const std::map<std::string, Status> strToStatusMap = {
            {"TENTATIVE", Status::TENTATIVE},
            {"CONFIRMED", Status::CONFIRMED},
            {"CANCELLED", Status::CANCELLED}
        };

        std::string lowerStr(status.toStdString());
        std::ranges::transform(lowerStr, lowerStr.begin(), ::tolower);

        auto it = strToStatusMap.find(lowerStr);
        if (it != strToStatusMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid status string");
        }
    }

    static Transparency stringToTransparency(const String& transp) {
        static const std::map<std::string, Transparency> strToTransparencyMap = {
            {"OPAQUE", Transparency::OPAQUE},
            {"TRANSPARENT", Transparency::TRANSPARENT}
        };

        std::string lowerStr(transp.toStdString());
        std::ranges::transform(lowerStr, lowerStr.begin(), ::tolower);

        auto it = strToTransparencyMap.find(lowerStr);
        if (it != strToTransparencyMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid transparency string");
        }
    }
};

} // touka

#endif //EVENTUTILS_H
