//
// Created by Touka on 2023/12/15.
//

#include "EventManager.h"
#include <sstream>
#include <unordered_map>

namespace touka {
    std::vector<Event> EventManager::parseICalFormat(std::istringstream& icalDataStream) {
        // TODO implement it
        // 获取数据行
        // 以行为单位进行解析
        // 获取METHOD,若非PUBLISH
        // 获取时区
        return {};
    }

    String EventManager::toICalFormat(const Event& evt) {
        std::ostringstream ss;
        ss << "BEGIN:VEVENT\n";
        ss << "UID:" << evt.get_uid().toStdString() << "\n";
        ss << "SUMMARY:" << evt.get_summary().toStdString() << "\n";
        ss << "DESCRIPTION:" << evt.get_description().toStdString() << "\n";
        ss << "CLASS:" << EventUtils::classificationToString(evt.get_classification()).toStdString() << "\n";
        ss << "STATUS:" << EventUtils::statusToString(evt.get_status()).toStdString() << "\n";
        // ss << "TRANSP:" << EventUtils::transparencyToString(evt.get_transp()).toStdString() << "\n";
        ss << "PRIORITY:" << EventUtils::priorityToString(evt.get_priority()).toStdString() << "\n";
        ss << "DTSTART:" << evt.get_dt_start().toString().toStdString() << "\n";
        ss << "DTEND:" << evt.get_dt_end().toString().toStdString() << "\n";
        ss << "DTSTAMP:" << evt.get_dt_stamp().toString().toStdString() << "\n";
        ss << "CREATED:" << evt.get_created().toString().toStdString() << "\n";
        ss << "LAST-MODIFIED:" << evt.get_last_modified().toString("yyyyMMddThhmmssZ").toStdString() << "\n";
        ss << "LOCATION:" << evt.get_location().toStdString() << "\n";
        ss << "TZID:" << QString::fromUtf8(evt.get_tz().id()).toStdString() << "\n";
        ss << "RRULE:" << evt.get_rrule() << "\n";
        ss << "RECURRENCE-NO:" << evt.get_recurrence_no() << "\n";
        // ss << "RDATE:" << evt.get_rdate().toString().toStdString() << "\n";
        ss << "END:VEVENT\n";
        return ss.str().data();
    }

    Event EventManager::iCalFormatToEvt(const String& icalDataStream) {

    }

    String EventManager::exportICalFormat(const std::vector<Event>& evts) {

    }

} // touka