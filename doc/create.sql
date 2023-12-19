
CREATE TABLE EventCategories
(
    category_id          INTEGER PRIMARY KEY,
    category_color       TEXT,
    category_name        TEXT,
    category_description TEXT
);

CREATE TABLE Alarm
(
    alarm_id              INTEGER PRIMARY KEY,
    alarm_time            DATETIME,
    alarm_description     TEXT,
    alarm_duration        INTEGER,
    alarm_repeat_interval INTEGER,
    alarm_sound           TEXT
);

CREATE TABLE Recurrence
(
    recurrence_id   INTEGER PRIMARY KEY,
    frequency       INTEGER,
    until           DATETIME,
    count           INTEGER,
    interval        INTEGER,
    workweek_starts INTEGER
);

CREATE TABLE RecurrenceDays
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    day           INTEGER
);

CREATE TABLE RecurrenceMonthDays
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    month_day     INTEGER
);

CREATE TABLE RecurrenceYearDays
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    year_day      INTEGER
);

CREATE TABLE RecurrenceWeekNumbers
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    week_number   INTEGER
);

CREATE TABLE RecurrenceMonths
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    month         INTEGER
);

CREATE TABLE RecurrenceSetPositions
(
    recurrence_id INTEGER REFERENCES Recurrence (recurrence_id),
    set_position  INTEGER
);

CREATE TABLE Event
(
    uid                    INTEGER PRIMARY KEY,
    summary                TEXT,
    description            TEXT,
    classification         TEXT,
    status                 TEXT,
    priority               TEXT,
    start_datetime         DATETIME,
    end_datetime           DATETIME,
    stamp_datetime         DATETIME,
    created_datetime       DATETIME,
    last_modified_datetime DATETIME,
    location               TEXT,
    timezone               TEXT,
    recurrence_no          INTEGER,
    base_event_id          INTEGER REFERENCES Event (uid)
);

CREATE TABLE EventRecurrenceDates
(
    event_id        INTEGER REFERENCES Event (uid),
    recurrence_date DATETIME
);

CREATE TABLE EventCategories
(
    event_id    INTEGER REFERENCES Event (uid),
    category_id INTEGER REFERENCES EventCategories (category_id)
);
