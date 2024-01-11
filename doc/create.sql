CREATE TABLE events
(
    uid           TEXT PRIMARY KEY,
    summary       TEXT,
    description   TEXT,
    status        INTEGER,
    priority      INTEGER,
    all_day       BOOLEAN,
    private       BOOLEAN,
    dt_start      TEXT,
    dt_end        TEXT,
    dt_stamp      TEXT,
    created       TEXT,
    last_modified TEXT,
    tz            TEXT,
    location      TEXT,
    alarm_time    TEXT,
    cate_id       TEXT,
    FOREIGN KEY (cate_id) REFERENCES event_categories (cate_id)
);

CREATE TABLE event_categories
(
    cate_id          TEXT PRIMARY KEY,
    cate_color       TEXT,
    cate_name        TEXT
);

CREATE TABLE recurrences
(
    event_uid TEXT PRIMARY KEY,
    freq      INTEGER,
    until     TEXT,
    count     INTEGER,
    interval  INTEGER,
    FOREIGN KEY (event_uid) REFERENCES events (uid)
);

CREATE TABLE byday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);

CREATE TABLE bymonthday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);

CREATE TABLE byyearday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);

CREATE TABLE byweekno
(
    recurrence_event_uid TEXT,
    week                 INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);

CREATE TABLE bymonth
(
    recurrence_event_uid TEXT,
    month                INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);

CREATE TABLE bysetpos
(
    recurrence_event_uid TEXT,
    position             INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);