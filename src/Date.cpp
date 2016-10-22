#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctime>

#include "Date.hpp"

using namespace std;

Date::Date()
{

}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
  setYear(year);
  setMonth(month);
  setDay(day);
}

Date::Date(string dayMonthYear)
{
  setDate(dayMonthYear);
  // sscanf(dayMonthYear.c_str(), "%d/%d/%d", &day, &month, &year);
}

void Date::setYear(unsigned int year)
{
  this->year = year;
}


void Date::setMonth(unsigned int month)
{
  this->month = month;
}

void Date::setDay(unsigned int day)
{
  this->day = day;
}

void Date::setDate(string date)
{
  if(sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
    {
      /* if day, month or year are not valid, make whole date invalid */
      setDay(0);
      setMonth(0);
      setYear(0);
    }
}

unsigned int Date::getYear() const
{
  return year;
}

unsigned int Date::getMonth() const
{
  return month;
}

unsigned int Date::getDay() const
{
  return day;
}

string Date::asString()
{
  stringstream ss;
  ss << to_string(day) << "/" << to_string(month) << "/" << to_string(year);
  return ss.str();
}

void Date::show()
{
  cout << day << "/" << month << "/" << year << endl;
}

bool Date::isLeapYear()
{
  
  if(year % 2 == 0 && year % 100 != 0)
    return true;
  else if(year % 400 == 0)
    return true;
  else
    return false;
}

unsigned int Date::nDays()
{
  if(month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    {
      if(isLeapYear())
	return 29;
      else
	return 28;
    }
  else
    return 31;
}

bool Date::isValid()
{
  if(day <= nDays() && (month > 0 && month < 13))
    return true;
  else
    return false;
}

bool Date::operator==(const Date &date)
{
  return year == date.getYear() && month == date.getMonth() && day == date.getDay();
}

bool Date::operator>=(const Date &date)
{
  int date1 = year * 10000 + month * 100 + day;
  int date2 = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();

  return (date1 >= date2);
}

bool Date::operator<=(const Date &date)
{
  int date1 = year * 10000 + month * 100 + day;
  int date2 = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();

  return (date1 <= date2);
}

bool Date::isEqualTo(const Date &date)
{
  return year == date.getYear() && month == date.getMonth() && day == date.getDay();
}

bool Date::isAfter(const Date &date)
{
  int date1 = year * 10000 + month * 100 + day;
  int date2 = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();

  return (date1 > date2);
}

bool Date::isBefore(const Date &date)
{
  return !isAfter(date) && !isEqualTo(date);
}

string realTime()
{
  time_t t = time(0); // time now

  struct tm * now = localtime(& t);

  int day = now->tm_mday;
  int month = now->tm_mon;
  int year = now->tm_year + 1900;

  Date newDate(day, month + 1, year);

  return newDate.asString();
}

