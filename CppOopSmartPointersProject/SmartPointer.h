#pragma once
template <typename T>
class SmartPointer
{
	T* resource;
public:
	SmartPointer(T* resource)
		: resource{ resource } {}

	SmartPointer(SmartPointer& other) = delete;
	//{
	//	resource = new T;
	//	*resource = *other.resource;
	//}

	SmartPointer(SmartPointer&& other) noexcept
	{
		resource = other.resource;
		other.resource = nullptr;
	}

	SmartPointer& operator=(const SmartPointer& other) = delete;
	//{
	//	if (&other == this)
	//		return *this;

	//	if (resource)
	//		delete resource;
	//	resource = new T;
	//	*resource = *other.resource;

	//	return *this;
	//}

	SmartPointer& operator=(SmartPointer&& other) noexcept
	{
		if (&other == this)
			return *this;

		delete this->resource;

		this->resource = other.resource;
		other.resource = nullptr;

		return *this;
	}



	T& operator*() const
	{
		return *resource;
	}

	T* operator->() const
	{
		return resource;
	}

	~SmartPointer()
	{
		delete resource;
	}
};

