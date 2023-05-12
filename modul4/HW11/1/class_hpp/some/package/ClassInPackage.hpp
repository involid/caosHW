#pragma once

namespace some::package {

class ClassInPackage {
 public:
  ClassInPackage();

  virtual ~ClassInPackage();

  virtual void SetValue(int);

  virtual int GetValue();

 private:
  int value;
};

}  // namespace some::package
