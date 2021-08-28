#include <locale>
void** text_hook = NULL;
void** line_hook = NULL;

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}


	T* Data;
private:
	int Count;
	int Max;
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{

	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	inline const char* cc_str() const
	{
		return std::string(Data, &Data[wcslen(Data)]).c_str();
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

namespace gui
{
	struct Vec4
	{
		float x;
		float y;
		float z;
		float w;

		Vec4() { x = y = z = w = 0.0; }
		Vec4(float xx, float yy, float zz, float ww) { x = xx; y = yy; z = zz; w = ww; }
	};

	struct FLinearColor
	{
		float R;
		float G; 
		float B;
		float A;

		inline FLinearColor()
			: R(0), G(0), B(0), A(0)
		{ }

		inline FLinearColor(float r, float g, float b, float a)
			: R(r / 255.0f),
			G(g / 255.0f),
			B(b / 255.0f),
			A(a / 255.0f)
		{ }
	};

	void text_function(void* hud, FString string, FLinearColor color, float x, float y)
	{
		if (!text_hook) return;
		if (!hud) return;

		auto text_function = reinterpret_cast<void(__fastcall*)(void*, FString, FLinearColor, float, float, void*, float)>(text_hook);
		return text_function(hud, string, color, x, y, nullptr, 1);
	}

	void draw_text(void* hud, FString string, FLinearColor color, float x, float y)
	{
		text_function(hud, string, FLinearColor(0, 0, 0, 200), x + 1, y + 1);
		text_function(hud, string, FLinearColor(0, 0, 0, 200), x - 1, y - 1);
		text_function(hud, string, FLinearColor(0, 0, 0, 200), x + 1, y - 1);
		text_function(hud, string, FLinearColor(0, 0, 0, 200), x - 1, y + 1);
		text_function(hud, string, color, x, y);
	}

	void create_menu(void* UCanvas)
	{

	}
}