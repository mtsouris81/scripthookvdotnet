/**
 * Copyright (C) 2015 crosire
 *
 * This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 * Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
 *      original  software. If you use this  software  in a product, an  acknowledgment in the product
 *      documentation would be appreciated but is not required.
 *   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
 *      being the original software.
 *   3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

namespace GTA
{
	#pragma region Forward Declarations
	ref class Viewport;
	ref class ScriptDomain;
	ref class ScriptSettings;
	#pragma endregion

	[System::AttributeUsage(System::AttributeTargets::Class, AllowMultiple = true)]
	public ref class RequireScript : System::Attribute
	{
	public:
		RequireScript(System::Type ^dependency) : _dependency(dependency) { }

	internal:
		System::Type ^_dependency;
	};

	public ref class Script abstract
	{
	public:
		Script();

		static void Wait(int ms);
		static void Yield();

		event System::EventHandler ^Tick
		{
			void add(System::EventHandler ^value);
			void remove(System::EventHandler ^value);
		}
		event System::Windows::Forms::KeyEventHandler ^KeyUp
		{
			void add(System::Windows::Forms::KeyEventHandler ^value);
			void remove(System::Windows::Forms::KeyEventHandler ^value);
		}
		event System::Windows::Forms::KeyEventHandler ^KeyDown
		{
			void add(System::Windows::Forms::KeyEventHandler ^value);
			void remove(System::Windows::Forms::KeyEventHandler ^value);
		}
		event System::EventHandler ^Aborted
		{
			void add(System::EventHandler ^value);
			void remove(System::EventHandler ^value);
		}

		System::Windows::Forms::Keys ActivateKey = System::Windows::Forms::Keys::NumPad5;
		System::Windows::Forms::Keys BackKey = System::Windows::Forms::Keys::NumPad0;
		System::Windows::Forms::Keys LeftKey = System::Windows::Forms::Keys::NumPad4;
		System::Windows::Forms::Keys RightKey = System::Windows::Forms::Keys::NumPad6;
		System::Windows::Forms::Keys UpKey = System::Windows::Forms::Keys::NumPad8;
		System::Windows::Forms::Keys DownKey = System::Windows::Forms::Keys::NumPad2;

		property System::String ^Name
		{
			System::String ^get()
			{
				return GetType()->FullName;
			}
		}
		property System::String ^Filename
		{
			System::String ^get()
			{
				return _filename;
			}
		}

		property Viewport ^View
		{
			Viewport ^get();
		}
		property ScriptSettings ^Settings
		{
			ScriptSettings ^get();
		}

		void Abort();

		virtual System::String ^ToString() override
		{
			return Name;
		}

	protected:
		property int Interval
		{
			int get();
			void set(int value);
		}

	internal:
		~Script();

		void HandleViewportDraw(System::Object ^sender, System::EventArgs ^e);
		void HandleViewportInput(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e);

		System::String ^_filename;
		Viewport ^_viewport;
		ScriptSettings ^_settings;
	};
}