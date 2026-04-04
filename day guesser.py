import random
import time


year = random.randint(1900,2099)

months = [
    "Jan",
    "Feb",
    "March",
    "April",
    "May",
    "June",
    "July",
    "Aug",
    "Sept",
    "Oct",
    "Nov",
    "Dec"
]
days = {
    "Jan" : 31,
    "Feb" : 28,
    "March" : 31,
    "April" : 30,
    "May" : 31,
    "June" : 30,
    "July" : 31,
    "Aug" : 31,
    "Sept": 30,
    "Oct": 31,
    "Nov" : 30,
    "Dec" : 31
}
map = {
    "Jan" : 6,
    "Feb" : 2,
    "March" : 2,
    "April" : 5,
    "May" : 0,
    "June" : 3,
    "July" : 5,
    "Aug" : 1,
    "Sept": 4,
    "Oct": 6,
    "Nov" : 2,
    "Dec" : 4
}

answer_day ={
    0 : "sunday",
    1 : "monday",
    2 : "tuesday",
    3 : "wednesday",
    4 : "thursday",
    5 : "friday",
    6 : "saturday"
}

def find_day(day,month,year):
    ans = 0
    if year % 4 == 0 and (month == "Jan" or month == "Feb"):
        ans = day + map.get(month)- 1
    else :
        ans = day + map.get(month)
    
    temp = year % 100
    temp = (temp + temp//4) % 7

    return (ans + temp) % 7 

curr_month = random.choice(months)
curr_day = 0

if curr_month == "Feb" and year % 4 == 0:
    curr_day = random.randint(1,29)
else:
    curr_day = random.randint(1, days.get(curr_month))

print("The day of :",curr_day ,curr_month , year, ":")
guess = str(input())
if year - 2000 < 0:
    curr_day += 1
if(guess == answer_day.get(find_day(curr_day,curr_month,year))):
    print("You are right")
else:
    print("Wrong, Expected: ", answer_day.get(find_day(curr_day, curr_month, year)))



print("Added a main change only")
print("Added in fork")
print("Ammended")
print("Another change in forked branched out branch")