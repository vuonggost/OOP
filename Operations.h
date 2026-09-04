#pragma once

#include <string>
#include "ContactManager.h"

using namespace std;

class ContactOperation {
public:
    virtual void execute(ContactManager& manager) = 0;
    virtual ~ContactOperation() = default;
};

class AddContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class SearchContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class UpdateContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class DeleteContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class FilterContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class SortContactOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class StatisticsOperation : public ContactOperation {
public:
    void execute(ContactManager& manager) override;
};

class LoadOperation : public ContactOperation {
private:
    string fileName;

public:
    LoadOperation(const string& fileName);
    void execute(ContactManager& manager) override;
};

class SaveOperation : public ContactOperation {
private:
    string fileName;

public:
    SaveOperation(const string& fileName);
    void execute(ContactManager& manager) override;
};
