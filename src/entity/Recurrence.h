//
// Created by Touka on 2023/12/15.
//

#ifndef RECURRENCE_H
#define RECURRENCE_H

#include <ostream>

#include "types.hpp"
#include <utils/DateUtil.h>

namespace touka {

class Recurrence {

public: 
    enum class Frequency {
        NONE=0,
        YEARLY,
        MONTHLY,
        WEEKLY,
        DAILY
    };

    [[nodiscard]] Frequency get_freq() const {
        return freq_;
    }

    void set_freq(const Frequency freq) {
        freq_ = freq;
    }

    [[nodiscard]] const std::optional<DateTime> &get_until() const {
      return until_;
    }

    void set_until(const DateTime& until) {
        until_ = until;
    }

    [[nodiscard]] std::optional<int> get_count() const { return count_; }

    void set_count(const int count) {
        count_ = count;
    }

    [[nodiscard]] uint16 get_interval() const {
        return interval_;
    }

    void set_interval(const uint16 interval) {
        interval_ = interval;
    }

    [[nodiscard]] const std::vector<Week>& get_byday() const {
        return byday_;
    }

    void set_byday(const std::vector<Week>& byday) {
        byday_ = byday;
    }

    [[nodiscard]] const std::vector<int>& get_bymonthday() const {
        return bymonthday_;
    }

    void set_bymonthday(const std::vector<int>& bymonthday) {
        bymonthday_ = bymonthday;
    }

    [[nodiscard]] const std::vector<int>& get_byyearday() const {
        return byyearday_;
    }

    void set_byyearday(const std::vector<int>& byyearday) {
        byyearday_ = byyearday;
    }

    [[nodiscard]] const std::vector<int>& get_byweekno() const {
        return byweekno_;
    }

    void set_byweekno(const std::vector<int>& byweekno) {
        byweekno_ = byweekno;
    }

    [[nodiscard]] const std::vector<int>& get_bymonth() const {
        return bymonth_;
    }

    void set_bymonth(const std::vector<int>& bymonth) {
        bymonth_ = bymonth;
    }

    [[nodiscard]] const std::vector<int>& get_bysetpos() const {
        return bysetpos_;
    }

    void set_bysetpos(const std::vector<int>& bysetpos) {
        bysetpos_ = bysetpos;
    }

    friend std::ostream& operator<<(std::ostream& os, const Recurrence& obj) {
        // TODO implement it
        return os;
               // << "freq_: " << obj.freq_
               // << " until_: " << obj.until_
               // << " count_: " << obj.count_
               // << " interval_: " << obj.interval_
               // << " bysecond_: " << obj.bysecond_
               // << " byminute_: " << obj.byminute_
               // << " byhour_: " << obj.byhour_
               // << " byday_: " << obj.byday_
               // << " bymonthday_: " << obj.bymonthday_
               // << " byyearday_: " << obj.byyearday_
               // << " byweekno_: " << obj.byweekno_
               // << " bymonth_: " << obj.bymonth_
               // << " bysetpos_: " << obj.bysetpos_
               // << " wkst_: " << obj.wkst_;
    }

private:
    Frequency freq_;            // The frequency of the recurrence
    std::optional<DateTime> until_; // The end date of the recurrence
    std::optional<int> count_;      // The number of occurrences
    uint16 interval_;           // The interval between each occurrence
    std::vector<Week> byday_;   // The days of the week
    std::vector<int> bymonthday_; // The days of the month
    std::vector<int> byyearday_;  // The days of the year
    std::vector<int> byweekno_;   // The week number of the year
    std::vector<int> bymonth_;    // The months of the year
    std::vector<int> bysetpos_;   // The position of the recurrence set
    // Week wkst_;                   // The day that the workweek starts

};

} // touka

#endif //RECURRENCE_H
