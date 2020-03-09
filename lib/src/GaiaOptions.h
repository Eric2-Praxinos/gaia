#pragma once

#ifndef GAIA_OPTIONS_H
#define GAIA_OPTIONS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

#define REGISTER_GAIAOPTION(Category, Name, Type, Value) \
namespace nOptions { \
	bool _ ## Category ## _ ## Name ## _= GaiaOptions::RegisterOption<Type>(#Category, #Name, Value); \
}

namespace nGaia {

class BaseOption {
public:
	virtual ~BaseOption() {}
	BaseOption() {}

public:
	virtual BaseOption* clone() = 0;
};

template<typename T>
class GaiaOption : public BaseOption {
public:
	/* destructor */
	~GaiaOption();

	/* constructor */
	GaiaOption(const T& iValue);

public:
	virtual BaseOption* clone();

public:
	void Set(const T& iValue);
	const T& Get() const;

private:
	T mValue;
};

/*
	* The base Gaia class
	*/
class GaiaOptions {
public:
	typedef std::map<std::pair<std::string, std::string>, BaseOption*> tOptionMap;

public:
	/* destructor */
	~GaiaOptions();
	/* constructor */
	GaiaOptions();

public:
	template <typename T> static bool RegisterOption(const std::string& iCategory, const std::string& iAttribute, const T& iDefaultValue);
	static GaiaOptions* DefaultOptions();

public:
	template <typename T> void Add(const std::string& iCategory, const std::string& iAttribute, const T& iDefaultValue);

	template <typename T> void Set(const std::string& iCategory, const std::string& iAttribute, const T& iValue);

	template <typename T> const T& Get(const std::string& iCategory, const std::string& iAttribute);

private:
	void InitWithDefaults();

private:
	tOptionMap mOptions;
};

// =========== GaiaOption

template<typename T>
GaiaOption<T>::~GaiaOption()
{
}

template<typename T>
GaiaOption<T>::GaiaOption(const T& iValue) :
	mValue(iValue)
{
}

template<typename T>
BaseOption*
GaiaOption<T>::clone() {
	return new GaiaOption(mValue);
}

template <typename T>
void
GaiaOption<T>::Set(const T& iValue) {
	mValue = iValue;
}

template <typename T>
const T&
GaiaOption<T>::Get() const {
	return mValue;
}

// =========== GaiaOptions

template <typename T>
bool
GaiaOptions::RegisterOption(const std::string& iCategory, const std::string& iAttribute, const T& iDefaultValue) {
	std::pair<std::string, std::string> pair = std::make_pair(iCategory, iAttribute);
	DefaultOptions()->Add(iCategory, iAttribute, iDefaultValue);
	return true;
}

template <typename T>
void
GaiaOptions::Add(const std::string& iCategory, const std::string& iAttribute, const T& iDefaultValue) {
	std::pair<std::string, std::string> pair = std::make_pair(iCategory, iAttribute);
	mOptions[pair] = new GaiaOption<T>(iDefaultValue);
}

template <typename T>
void
GaiaOptions::Set(const std::string& iCategory, const std::string& iAttribute, const T& iValue) {
	const std::pair<std::string, std::string> pair = std::make_pair(iCategory, iAttribute);
	GaiaOption<T>* option = dynamic_cast<GaiaOption<T>*>(mOptions[pair]);
	option->Set(iValue);
}

template <typename T>
const T&
GaiaOptions::Get(const std::string& iCategory, const std::string& iAttribute) {
	const std::pair<std::string, std::string> pair = std::make_pair(iCategory, iAttribute);
	PGUIOption<T>* option = dynamic_cast<PGUIOption<T>*>(mOptions[pair]);
	return option->Get();
}

}

#endif