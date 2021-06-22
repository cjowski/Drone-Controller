#include "UndefinedSerialTask.h"

UndefinedSerialTask::UndefinedSerialTask(StringListDecoderOutput *decoderOutput)
{
  std::list<String> texts = decoderOutput->GetTexts();
  auto it = texts.begin();
  TaskID = (*it).toInt();
  it++;
  TaskType = (*it).toInt();

  if (it != texts.end())
  {
    it++;
    for (auto it2 = it; it2 != texts.end(); it2++)
    {
      OtherSerialTexts.push_back(*it2);
    }
  }
}

bool UndefinedSerialTask::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isdigit(currentChar) && currentChar != '-') {
      return false;
    }
  }
  return true;
}

bool UndefinedSerialTask::SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput)
{
  StringListDecoderOutput *stringListDecoderOutput = (StringListDecoderOutput*)decoderOutput;

  if (stringListDecoderOutput->GetKey() != StmTask::SERIAL_KEY
    || stringListDecoderOutput->GetTexts().size() < MIN_SERIAL_TEXTS_COUNT
  )
  {
    return false;
  }

  auto it = stringListDecoderOutput->GetTexts().begin();
  if (!IsInteger(*it) && (*it).toInt() > 0)
  {
    return false;
  }

  it++;
  if (!IsInteger(*it) && (*it).toInt() > 0)
  {
    return false;
  }

  return true;
}

int UndefinedSerialTask::GetTaskID()
{
  return TaskID;
}

int UndefinedSerialTask::GetTaskType()
{
  return TaskType;
}