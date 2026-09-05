#pragma once
#include "ContactManager.h"
#include <string>

using namespace std;


class ContactOperation
{
public:
    virtual void execute(ContactManager* manager) = 0;
    virtual ~ContactOperation() = default;
};

class AddContactOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class SearchByNameOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class SearchByPhonePrefixOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class UpdateContactOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class DeleteContactOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class FilterContactOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class StatisticsOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class ExportByRelationshipOperation : public ContactOperation
{
public:
    void execute(ContactManager* manager) override;
};

class LoadContactOperation : public ContactOperation
{
private:
    string filename;

public:
    explicit LoadContactOperation(string filename);
    void execute(ContactManager* manager) override;
};

class SaveContactOperation : public ContactOperation
{
private:
    string filename;

public:
    explicit SaveContactOperation(string filename);
    void execute(ContactManager* manager) override;
};
