#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};

	private:
		Type type;
		u8 code;

	public:
		Event() noexcept :
			type( Type::Invalid),
			code( 0u )
		{}
		Event(Type type, u8 code) noexcept :
			type(type),
			code(code)
		{}

		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}

		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}

		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}

		u8 GetCode() const noexcept
		{
			return code;
		}
	};

public:
	Keyboard() = default;
	Keyboard(const Keyboard& kb) = delete;
	Keyboard& operator= (const Keyboard& kb) = delete;

	//Key event stuff
	bool KeyIsPressed(u8 keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	//Char event stuff
	u8 ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	//autorepeat control
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;

	void OnKeyPressed(u8 keycode) noexcept;
	void OnKeyReleased(u8 keycode) noexcept;
	void OnChar(u8 character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;

private:
	static constexpr u32 nKeys = 256u;
	static constexpr u32 bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<u8> charBuffer;
};