#pragma once

#include "VFrameReader.h"
#include "ComboboxItem.h"
#include <vector>
#include <string>
#include <iostream>
#include <codecvt>
#include <vcclr.h>
#include <list>

namespace ThirdEye {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
		public: MainWindow(void);
		protected: ~MainWindow();
		private: System::Windows::Forms::SplitContainer^ MainContainer;
		protected:

		private: System::Windows::Forms::Label^ CaptureViewLabel;
		private: System::Windows::Forms::PictureBox^ CaptureView;
		private: System::Windows::Forms::Label^ TextViewLabel;
	private: System::Windows::Forms::Label^ ConsoleLabel;

		private: System::Windows::Forms::RichTextBox^ ObjectView;
		private: System::Windows::Forms::Label^ ObjectViewLabel;
		private: System::Windows::Forms::RichTextBox^ TextView;
		private: System::Windows::Forms::RichTextBox^ richTextBox1;
		private: System::Windows::Forms::Label^ OpenCVViewLabel;
		private: System::Windows::Forms::PictureBox^ OpenCVView;
	private: System::Windows::Forms::ComboBox^ WindowSelection;
	private: System::ComponentModel::BackgroundWorker^ WindowCaptureWorker;



		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;

			// vframe member
			ThirdEye::VFrameReader^ vreader;

		#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->MainContainer = (gcnew System::Windows::Forms::SplitContainer());
				this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
				this->ConsoleLabel = (gcnew System::Windows::Forms::Label());
				this->ObjectView = (gcnew System::Windows::Forms::RichTextBox());
				this->ObjectViewLabel = (gcnew System::Windows::Forms::Label());
				this->TextView = (gcnew System::Windows::Forms::RichTextBox());
				this->TextViewLabel = (gcnew System::Windows::Forms::Label());
				this->WindowSelection = (gcnew System::Windows::Forms::ComboBox());
				this->OpenCVView = (gcnew System::Windows::Forms::PictureBox());
				this->OpenCVViewLabel = (gcnew System::Windows::Forms::Label());
				this->CaptureViewLabel = (gcnew System::Windows::Forms::Label());
				this->CaptureView = (gcnew System::Windows::Forms::PictureBox());
				this->WindowCaptureWorker = (gcnew System::ComponentModel::BackgroundWorker());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainContainer))->BeginInit();
				this->MainContainer->Panel1->SuspendLayout();
				this->MainContainer->Panel2->SuspendLayout();
				this->MainContainer->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpenCVView))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CaptureView))->BeginInit();
				this->SuspendLayout();
				// 
				// MainContainer
				// 
				this->MainContainer->Dock = System::Windows::Forms::DockStyle::Fill;
				this->MainContainer->Location = System::Drawing::Point(0, 0);
				this->MainContainer->Name = L"MainContainer";
				// 
				// MainContainer.Panel1
				// 
				this->MainContainer->Panel1->Controls->Add(this->richTextBox1);
				this->MainContainer->Panel1->Controls->Add(this->ConsoleLabel);
				this->MainContainer->Panel1->Controls->Add(this->ObjectView);
				this->MainContainer->Panel1->Controls->Add(this->ObjectViewLabel);
				this->MainContainer->Panel1->Controls->Add(this->TextView);
				this->MainContainer->Panel1->Controls->Add(this->TextViewLabel);
				// 
				// MainContainer.Panel2
				// 
				this->MainContainer->Panel2->Controls->Add(this->WindowSelection);
				this->MainContainer->Panel2->Controls->Add(this->OpenCVView);
				this->MainContainer->Panel2->Controls->Add(this->OpenCVViewLabel);
				this->MainContainer->Panel2->Controls->Add(this->CaptureViewLabel);
				this->MainContainer->Panel2->Controls->Add(this->CaptureView);
				this->MainContainer->Size = System::Drawing::Size(1423, 581);
				this->MainContainer->SplitterDistance = 701;
				this->MainContainer->TabIndex = 0;
				// 
				// richTextBox1
				// 
				this->richTextBox1->Location = System::Drawing::Point(3, 398);
				this->richTextBox1->Name = L"richTextBox1";
				this->richTextBox1->Size = System::Drawing::Size(693, 137);
				this->richTextBox1->TabIndex = 8;
				this->richTextBox1->Text = L"";
				// 
				// ConsoleLabel
				// 
				this->ConsoleLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->ConsoleLabel->AutoSize = true;
				this->ConsoleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->ConsoleLabel->Location = System::Drawing::Point(3, 375);
				this->ConsoleLabel->Name = L"ConsoleLabel";
				this->ConsoleLabel->Size = System::Drawing::Size(74, 20);
				this->ConsoleLabel->TabIndex = 7;
				this->ConsoleLabel->Text = L"Console";
				// 
				// ObjectView
				// 
				this->ObjectView->Location = System::Drawing::Point(3, 215);
				this->ObjectView->Name = L"ObjectView";
				this->ObjectView->Size = System::Drawing::Size(693, 157);
				this->ObjectView->TabIndex = 6;
				this->ObjectView->Text = L"";
				// 
				// ObjectViewLabel
				// 
				this->ObjectViewLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->ObjectViewLabel->AutoSize = true;
				this->ObjectViewLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->ObjectViewLabel->Location = System::Drawing::Point(3, 192);
				this->ObjectViewLabel->Name = L"ObjectViewLabel";
				this->ObjectViewLabel->Size = System::Drawing::Size(126, 20);
				this->ObjectViewLabel->TabIndex = 5;
				this->ObjectViewLabel->Text = L"Objects Found";
				// 
				// TextView
				// 
				this->TextView->Location = System::Drawing::Point(3, 32);
				this->TextView->Name = L"TextView";
				this->TextView->Size = System::Drawing::Size(693, 157);
				this->TextView->TabIndex = 4;
				this->TextView->Text = L"";
				this->TextView->Visible = false;
				// 
				// TextViewLabel
				// 
				this->TextViewLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->TextViewLabel->AutoSize = true;
				this->TextViewLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->TextViewLabel->Location = System::Drawing::Point(3, 9);
				this->TextViewLabel->Name = L"TextViewLabel";
				this->TextViewLabel->Size = System::Drawing::Size(99, 20);
				this->TextViewLabel->TabIndex = 2;
				this->TextViewLabel->Text = L"Text Found";
				// 
				// WindowSelection
				// 
				this->WindowSelection->FormattingEnabled = true;
				this->WindowSelection->Location = System::Drawing::Point(334, 5);
				this->WindowSelection->Name = L"WindowSelection";
				this->WindowSelection->Size = System::Drawing::Size(372, 21);
				this->WindowSelection->TabIndex = 4;
				this->WindowSelection->SelectionChangeCommitted += gcnew System::EventHandler(this, &MainWindow::WindowSelection_SelectionChangeCommitted);
				// 
				// OpenCVView
				// 
				this->OpenCVView->Location = System::Drawing::Point(6, 354);
				this->OpenCVView->Name = L"OpenCVView";
				this->OpenCVView->Size = System::Drawing::Size(712, 215);
				this->OpenCVView->TabIndex = 3;
				this->OpenCVView->TabStop = false;
				// 
				// OpenCVViewLabel
				// 
				this->OpenCVViewLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->OpenCVViewLabel->AutoSize = true;
				this->OpenCVViewLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->OpenCVViewLabel->Location = System::Drawing::Point(3, 331);
				this->OpenCVViewLabel->Name = L"OpenCVViewLabel";
				this->OpenCVViewLabel->Size = System::Drawing::Size(119, 20);
				this->OpenCVViewLabel->TabIndex = 2;
				this->OpenCVViewLabel->Text = L"OpenCV View";
				// 
				// CaptureViewLabel
				// 
				this->CaptureViewLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->CaptureViewLabel->AutoSize = true;
				this->CaptureViewLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->CaptureViewLabel->Location = System::Drawing::Point(3, 9);
				this->CaptureViewLabel->Name = L"CaptureViewLabel";
				this->CaptureViewLabel->Size = System::Drawing::Size(82, 20);
				this->CaptureViewLabel->TabIndex = 1;
				this->CaptureViewLabel->Text = L"Captures";
				// 
				// CaptureView
				// 
				this->CaptureView->Location = System::Drawing::Point(3, 32);
				this->CaptureView->Name = L"CaptureView";
				this->CaptureView->Size = System::Drawing::Size(712, 296);
				this->CaptureView->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				this->CaptureView->TabIndex = 0;
				this->CaptureView->TabStop = false;
				// 
				// WindowCaptureWorker
				// 
				this->WindowCaptureWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainWindow::WindowCaptureWorker_DoWork);
				this->WindowCaptureWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainWindow::WindowCaptureWorker_RunWorkerCompleted);
				// 
				// MainWindow
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1423, 581);
				this->Controls->Add(this->MainContainer);
				this->Name = L"MainWindow";
				this->Text = L"ThirdEye Assistance ALPHA";
				this->MainContainer->Panel1->ResumeLayout(false);
				this->MainContainer->Panel1->PerformLayout();
				this->MainContainer->Panel2->ResumeLayout(false);
				this->MainContainer->Panel2->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainContainer))->EndInit();
				this->MainContainer->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpenCVView))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CaptureView))->EndInit();
				this->ResumeLayout(false);

			}
		#pragma endregion


private: System::Void WindowSelection_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e);
private: System::Void WindowCaptureWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
private: System::Void WindowCaptureWorker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
};
}
