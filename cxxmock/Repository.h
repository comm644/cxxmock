#ifndef __cxxmock__REPOSITORY_H
#define __cxxmock__REPOSITORY_H
#include <map>
#include <string>
#include <cxxmock/Handle.h>
#include <cxxmock/CallInfo.h>
#include <cxxmock/Factory.h>

namespace CxxMock
{

class MockObject;
class Repository
{
	friend class MockObject;

	typedef std::list<MockObject*> MocksInUseList;
	typedef std::map<string, Handle*> RepositoryTypeMap;

private:
	static RepositoryTypeMap _registry;
	static Repository* _instance;
	bool _isRecording;
	bool _isVerified;

	MocksInUseList _mocks;
	CallInfo* _lastCall;

	MocksInUseList _deleteIt;
private:
	void registerMock( MockObject* ptr )
	{
		_mocks.push_back(ptr);
	}
	void unregisterMock( MockObject* ptr )
	{
		_mocks.remove(ptr);
	}

	void setLastCall( CallInfo* info)
	{
		_lastCall = info;
	}

	void  operator=(const Repository&);

	Repository(const Repository& );

public:
	static Repository& instance()
	{
		return *_instance;
	}

public:

	Repository() :
		_isRecording(true),
		_isVerified(false),
		_lastCall(0)
	{
		_instance = this;
	}
	~Repository()
	{
		if( !_isVerified ) {
			//verify();
		}
	}

	template<class T>
	void registerFactory(Factory<T>* factory)
	{
		string tname = typeid( typename Factory<T>::TargetType ).name();
		_registry[ tname ] = factory;
	}

	template<class T>
	T* create()
	{
		string tname = typeid(T).name();

		RepositoryTypeMap::iterator it = _registry.find(tname);
		if ( it == _registry.end()) {
			throw  InvalidArgumentException( string("Mock factory for ") + tname + " not found.");
		}
		return dynamic_cast< Factory<T>* >(&(*it->second))->create();
	}


	template<typename R>
	CallInfo& expectCall( R ) {
		return *_lastCall;
	}

	CallInfo& expectCall() {
		return *_lastCall;
	}

	void replay()
	{
		_isRecording = false;
	}
	void recording()
	{
		_isRecording = true;
	}
	bool isRecording()
	{
		return _isRecording;
	}

	void verify();

	void expectionFailed()
	{
		//ignore verification.
		_isVerified = true;
	}
};

Repository* Repository::_instance = NULL;
Repository::RepositoryTypeMap Repository::_registry;


}


#endif // __cxxmock__REPOSITORY_H
