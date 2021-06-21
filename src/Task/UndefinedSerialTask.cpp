// #include "UndefinedSerialTask.h"

// UndefinedSerialTask::UndefinedSerialTask(std::list<String> serialValues)
// {
//   auto it = serialValues.begin();
//   TaskID = (*it).toInt();
//   it++;
//   TaskType = (*it).toInt();
//   it++;
//   for (auto it2 = it; it2 != serialValues.end(); it2++)
//   {
//     OtherSerialValues.push_back(*it2);
//   }
// }

// bool UndefinedSerialTask::IsInteger(String text) {
//   for(char i = 0; i < text.length(); i++) {
//     char currentChar = text.charAt(i);
//     if (!isdigit(currentChar) && currentChar != '-') {
//       return false;
//     }
//   }
//   return true;
// }

// bool UndefinedSerialTask::SerialValuesMatched(std::list<String> serialValues)
// {
//   if (serialValues.size() < MIN_SERIAL_VALUE_COUNT)
//   {
//     return false;
//   }

//   auto it = serialValues.begin();
//   if (!IsInteger(*it) && (*it).toInt() > 0)
//   {
//     return false;
//   }

//   it++;
//   if (!IsInteger(*it) && (*it).toInt() > 0)
//   {
//     return false;
//   }

//   return true;
// }

// int UndefinedSerialTask::GetTaskID()
// {
//   return TaskID;
// }

// int UndefinedSerialTask::GetTaskType()
// {
//   return TaskType;
// }

// std::list<String> UndefinedSerialTask::GetOtherSerialValues()
// {
//   return OtherSerialValues;
// }

// std::list<String> UndefinedSerialTask::GetPrintStrings()
// {
//   std::list<String> printStrings;
//   printStrings.push_back(String(TaskID));
//   printStrings.push_back(String(TaskType));
//   for (auto it = OtherSerialValues.begin(); it != OtherSerialValues.end(); it++)
//   {
//     printStrings.push_back(*it);
//   }
//   return printStrings;
// }