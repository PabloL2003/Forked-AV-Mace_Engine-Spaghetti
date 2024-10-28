#pragma once

class BufferObject
{
	unsigned int _id = 0;
	int _target = 0x8892;

public:
	BufferObject() = default;
	BufferObject(BufferObject&& other) noexcept;
	BufferObject& operator=(BufferObject&& other) noexcept;
	BufferObject(const BufferObject&) = delete;
	BufferObject& operator=(const BufferObject&) = delete;
	~BufferObject();

	unsigned int id() const { return _id; }
	bool isLoaded() const { return _id != 0; }
	int target() const { return _target; }

	void bind() const;
	void unbind();

	void loadData(size_t size, const void* data);
	void loadIndices(size_t count, const unsigned int* data);
	template <typename T> void loadElements(size_t count, const T* data) { loadData(count * sizeof(T), data); }

private:
	void loadData(int target, size_t size, const void* data);
};

