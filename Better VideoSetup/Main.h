#pragma once

struct Resolution
{
	int width;
	int height;

	Resolution()
	{
		width = 0;
		height = 0;
	}

	Resolution(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	bool operator ==(Resolution res)
	{
		return this->width == res.width && this->height == res.height;
	}
};

#include <vector>
#include <iostream>

extern std::string currentPath;
extern std::string configPath;
extern std::vector<Resolution> resolutions;

namespace BetterVideoSetup 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();

			GetDrivers();
			GetSettings();
		}

	protected:
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ cancelButton;
	protected:
	private: System::Windows::Forms::Button^ okButton;
	private: System::Windows::Forms::ComboBox^ driverComboBox;
	private: System::Windows::Forms::Label^ driverLabel;
	private: System::Windows::Forms::Label^ resolutionLabel;
	private: System::Windows::Forms::ComboBox^ resolutionComboBox;
	private: System::Windows::Forms::CheckBox^ improveCheckBox;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->driverComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->driverLabel = (gcnew System::Windows::Forms::Label());
			this->resolutionLabel = (gcnew System::Windows::Forms::Label());
			this->resolutionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->improveCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(281, 94);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(54, 23);
			this->cancelButton->TabIndex = 0;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &Main::cancelButton_Click);
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(221, 94);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(54, 23);
			this->okButton->TabIndex = 1;
			this->okButton->Text = L"Ok";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &Main::okButton_Click);
			// 
			// driverComboBox
			// 
			this->driverComboBox->FormattingEnabled = true;
			this->driverComboBox->Location = System::Drawing::Point(90, 17);
			this->driverComboBox->Name = L"driverComboBox";
			this->driverComboBox->Size = System::Drawing::Size(245, 21);
			this->driverComboBox->TabIndex = 2;
			// 
			// driverLabel
			// 
			this->driverLabel->AutoSize = true;
			this->driverLabel->Location = System::Drawing::Point(46, 20);
			this->driverLabel->Name = L"driverLabel";
			this->driverLabel->Size = System::Drawing::Size(38, 13);
			this->driverLabel->TabIndex = 3;
			this->driverLabel->Text = L"Driver:";
			// 
			// resolutionLabel
			// 
			this->resolutionLabel->AutoSize = true;
			this->resolutionLabel->Location = System::Drawing::Point(24, 47);
			this->resolutionLabel->Name = L"resolutionLabel";
			this->resolutionLabel->Size = System::Drawing::Size(60, 13);
			this->resolutionLabel->TabIndex = 5;
			this->resolutionLabel->Text = L"Resolution:";
			// 
			// resolutionComboBox
			// 
			this->resolutionComboBox->FormattingEnabled = true;
			this->resolutionComboBox->Location = System::Drawing::Point(90, 44);
			this->resolutionComboBox->Name = L"resolutionComboBox";
			this->resolutionComboBox->Size = System::Drawing::Size(245, 21);
			this->resolutionComboBox->TabIndex = 4;
			// 
			// improveCheckBox
			// 
			this->improveCheckBox->AutoSize = true;
			this->improveCheckBox->Location = System::Drawing::Point(14, 71);
			this->improveCheckBox->Name = L"improveCheckBox";
			this->improveCheckBox->Size = System::Drawing::Size(321, 17);
			this->improveCheckBox->TabIndex = 6;
			this->improveCheckBox->Text = L"Improve the gameplay with the help of a customized dgvoodoo";
			this->improveCheckBox->UseVisualStyleBackColor = true;
			this->improveCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Main::improveCheckBox_CheckedChanged);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(347, 128);
			this->Controls->Add(this->improveCheckBox);
			this->Controls->Add(this->resolutionLabel);
			this->Controls->Add(this->resolutionComboBox);
			this->Controls->Add(this->driverLabel);
			this->Controls->Add(this->driverComboBox);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->cancelButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Better VideoSetup";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Close();
	}

	private: void GetDrivers();
	private: void GetSettings();
	private: void SaveSettings();

	private: System::Void improveCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (improveCheckBox->Checked)
			if (System::Windows::Forms::DialogResult::No == MessageBox::Show("After the agreement, additional dgVoodoo program files will be created to improve the operation of the game. Do you agree?", "Information", MessageBoxButtons::YesNo, MessageBoxIcon::Information))
				improveCheckBox->Checked = false;
	}

	private: System::Void okButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SaveSettings();
	}
};
}
