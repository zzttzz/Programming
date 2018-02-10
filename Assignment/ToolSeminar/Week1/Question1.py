from datetime import datetime, timezone, timedelta
import re

###pattern
r_date = "\d\d\d\d-[0-1]?\d-[0-3]?\d"
r_time = "\d?\d:\d\d:\d\d"
r_zone = "UTC[\+-]?[0-1]?\d:\d\d"


def to_timestamp(dt_str, tz_str):
    date=re.search(r_date, dt_str).group()
    time=re.search(r_time, dt_str).group()
    zone=re.search(r_zone, tz_str).group()
    if date and time and zone:
        l_date=re.split(r"-",date)
        l_time=re.split(r":",time)
        tz_h=int(re.search("[0-1]?\d",zone).group(0))
        tz_m=int(re.findall("\d\d",zone)[-1])
        i=1
        if re.search("-",zone):
            i=-1
        td=timedelta(0,0,0,0,tz_m*i,tz_h*i,0)
        year=int(l_date[0])
        month=int(l_date[1])
        day=int(l_date[2])
        hour=int(l_time[0])
        mintue=int(l_time[1])
        second=int(l_time[2])
        tz=timezone(td)
        gt=datetime(year,month,day,hour,mintue,second,0,tz)
        ep=datetime(1970,1,1,0,0,0,0,timezone(timedelta(0)))
        ts=int((gt-ep).total_seconds())
        return  ts



if __name__ == '__main__':

    # Test:
    t1 = to_timestamp('2015-6-1 08:10:30', 'UTC+7:00')
    assert t1 == 1433121030.0, t1

    t2 = to_timestamp('2015-5-31 16:10:30', 'UTC-09:00')
    assert t2 == 1433121030.0, t2

    print('ok')