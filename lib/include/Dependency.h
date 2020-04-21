#include <list>
#include <algorithm>

class cDependency
{
public:
    // default constructor
    ~cDependency()
	{
	}

    // assignment constructor
    cDependency() :
		mUpDependencies({}),
		mDownDependencies({})
	{
	}

public:
	void BeforeChange()
	{
		::std::list<cDependency*> dependencies = getAllDownDependencies();
		::std::for_each(dependencies.begin(), dependencies.end(), [this](cDependency* iDependency) { iDependency->OnDependencyBeforeChanged(const_cast<cDependency*>(this)); });
	}

	void AfterChange()
	{
		::std::list<cDependency*> dependencies = getAllDownDependencies();
		::std::for_each(dependencies.begin(), dependencies.end(), [this](cDependency* iDependency) { iDependency->OnDependencyAfterChanged(const_cast<cDependency*>(this)); });
	}

	void ClearUpDependencies()
	{
		::std::for_each(mUpDependencies.begin(), mUpDependencies.end(), [this](cDependency* iDependency) { iDependency->RemoveDownDependency(const_cast<cDependency*>(this)); });
		mUpDependencies.clear();
	}

	void AddUpDependency(cDependency* iDependency) {
		mUpDependencies.push_back(iDependency);
		iDependency->AddDownDependency(this);
	}

public:
	virtual void OnDependencyBeforeChanged(const cDependency* iDependency) = 0;
	virtual void OnDependencyAfterChanged(const cDependency* iDependency) = 0;

private:
	::std::list<cDependency*> getAllDownDependencies()
	{
		::std::list<cDependency*> dependencies = mDownDependencies;
		::std::for_each(mDownDependencies.begin(), mDownDependencies.end(), [&dependencies](cDependency* iDependency)
		{
			::std::list<cDependency*> deps = iDependency->getAllDownDependencies();
			::std::for_each(deps.begin(), deps.end(), [&dependencies](cDependency* iDep)
			{
				dependencies.push_back(iDep);
			});
		});
		return dependencies;
	}

	void AddDownDependency(cDependency* iDependency) {
		mDownDependencies.push_back(iDependency);
	}

	void RemoveDownDependency(cDependency* iDependency) {
		mDownDependencies.remove(iDependency);
	}

private:
	::std::list<cDependency*> mUpDependencies;
	::std::list<cDependency*> mDownDependencies;
};
