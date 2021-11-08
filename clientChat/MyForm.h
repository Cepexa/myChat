#pragma once
#include "../ddlSocket/Socket.h"

namespace clientChat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnAuth;
	private: System::Windows::Forms::TextBox^ tbLogin;
	protected:

	private: System::Windows::Forms::TextBox^ tbPass;

	private: System::Windows::Forms::Button^ btnRegist;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ tbIpServ;
	private: System::Windows::Forms::TextBox^ tbPortServ;



	private: System::Windows::Forms::TextBox^ tbMsg;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::TextBox^ tbContent;
	private: System::Windows::Forms::TextBox^ tbAnswer;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::SplitContainer^ splitContainer2;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnAuth = (gcnew System::Windows::Forms::Button());
			this->tbLogin = (gcnew System::Windows::Forms::TextBox());
			this->tbPass = (gcnew System::Windows::Forms::TextBox());
			this->btnRegist = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbIpServ = (gcnew System::Windows::Forms::TextBox());
			this->tbPortServ = (gcnew System::Windows::Forms::TextBox());
			this->tbMsg = (gcnew System::Windows::Forms::TextBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->tbContent = (gcnew System::Windows::Forms::TextBox());
			this->tbAnswer = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnAuth
			// 
			this->btnAuth->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnAuth->Location = System::Drawing::Point(443, 100);
			this->btnAuth->Name = L"btnAuth";
			this->btnAuth->Size = System::Drawing::Size(103, 29);
			this->btnAuth->TabIndex = 0;
			this->btnAuth->Text = L"Вход";
			this->btnAuth->UseVisualStyleBackColor = true;
			this->btnAuth->Click += gcnew System::EventHandler(this, &MyForm::btnAuth_Click);
			// 
			// tbLogin
			// 
			this->tbLogin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbLogin->Location = System::Drawing::Point(313, 42);
			this->tbLogin->Name = L"tbLogin";
			this->tbLogin->Size = System::Drawing::Size(233, 22);
			this->tbLogin->TabIndex = 1;
			this->tbLogin->Text = L"UserName";
			// 
			// tbPass
			// 
			this->tbPass->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPass->Location = System::Drawing::Point(313, 71);
			this->tbPass->Name = L"tbPass";
			this->tbPass->PasswordChar = '*';
			this->tbPass->Size = System::Drawing::Size(233, 22);
			this->tbPass->TabIndex = 2;
			// 
			// btnRegist
			// 
			this->btnRegist->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnRegist->Location = System::Drawing::Point(313, 100);
			this->btnRegist->Name = L"btnRegist";
			this->btnRegist->Size = System::Drawing::Size(124, 28);
			this->btnRegist->TabIndex = 3;
			this->btnRegist->Text = L"Регистрация";
			this->btnRegist->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(253, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Логин";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(253, 76);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Пароль";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(253, 15);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(56, 17);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Сервер";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(440, 15);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(39, 17);
			this->label4->TabIndex = 4;
			this->label4->Text = L"порт";
			// 
			// tbIpServ
			// 
			this->tbIpServ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbIpServ->Location = System::Drawing::Point(313, 14);
			this->tbIpServ->Name = L"tbIpServ";
			this->tbIpServ->Size = System::Drawing::Size(121, 22);
			this->tbIpServ->TabIndex = 5;
			this->tbIpServ->Text = L"192.168.1.101";
			// 
			// tbPortServ
			// 
			this->tbPortServ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPortServ->Location = System::Drawing::Point(485, 15);
			this->tbPortServ->Name = L"tbPortServ";
			this->tbPortServ->Size = System::Drawing::Size(61, 22);
			this->tbPortServ->TabIndex = 5;
			this->tbPortServ->Text = L"5000";
			// 
			// tbMsg
			// 
			this->tbMsg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbMsg->Enabled = false;
			this->tbMsg->Location = System::Drawing::Point(0, 0);
			this->tbMsg->Multiline = true;
			this->tbMsg->Name = L"tbMsg";
			this->tbMsg->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbMsg->Size = System::Drawing::Size(352, 100);
			this->tbMsg->TabIndex = 7;
			this->tbMsg->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tbMsg_KeyDown);
			this->tbMsg->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tbMsg_KeyUp);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->tbContent);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->tbMsg);
			this->splitContainer1->Size = System::Drawing::Size(352, 335);
			this->splitContainer1->SplitterDistance = 231;
			this->splitContainer1->TabIndex = 8;
			// 
			// tbContent
			// 
			this->tbContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbContent->Enabled = false;
			this->tbContent->Location = System::Drawing::Point(0, 0);
			this->tbContent->Multiline = true;
			this->tbContent->Name = L"tbContent";
			this->tbContent->ReadOnly = true;
			this->tbContent->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbContent->Size = System::Drawing::Size(352, 231);
			this->tbContent->TabIndex = 9;
			// 
			// tbAnswer
			// 
			this->tbAnswer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbAnswer->Enabled = false;
			this->tbAnswer->Location = System::Drawing::Point(0, 0);
			this->tbAnswer->Multiline = true;
			this->tbAnswer->Name = L"tbAnswer";
			this->tbAnswer->ReadOnly = true;
			this->tbAnswer->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbAnswer->Size = System::Drawing::Size(178, 335);
			this->tbAnswer->TabIndex = 9;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// splitContainer2
			// 
			this->splitContainer2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer2->Location = System::Drawing::Point(12, 134);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->tbAnswer);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->splitContainer1);
			this->splitContainer2->Size = System::Drawing::Size(534, 335);
			this->splitContainer2->SplitterDistance = 178;
			this->splitContainer2->TabIndex = 10;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(561, 481);
			this->Controls->Add(this->splitContainer2);
			this->Controls->Add(this->tbPortServ);
			this->Controls->Add(this->tbIpServ);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnRegist);
			this->Controls->Add(this->tbPass);
			this->Controls->Add(this->tbLogin);
			this->Controls->Add(this->btnAuth);
			this->MinimumSize = System::Drawing::Size(340, 425);
			this->Name = L"MyForm";
			this->Text = L"Client";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel1->PerformLayout();
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		MySocket* socket_sender;
		MySocket* socket_listener;
		bool stopped = true;
		System::Void btnAuth_Click(System::Object^ sender, System::EventArgs^ e) {
			if (stopped) {
				stopped = false;
				tbMsg->Enabled = true;
				tbAnswer->Enabled = true;
				tbContent->Enabled = true;
				tbIpServ->Enabled = false;
				tbPass->Enabled = false;
				tbPortServ->Enabled = false;
				tbLogin->Enabled = false;
				btnRegist->Enabled = false;
				btnAuth->Text = "Выход";
				socket_sender = new MySocket();
				string answer = socket_sender->sender(
					marshal_as<string>(tbIpServ->Text),
					marshal_as<string>(tbPortServ->Text),
					marshal_as<string>(tbLogin->Text));
				tbAnswer->AppendText(marshal_as<String^>(answer + "\n"));
				socket_listener = new MySocket();
				socket_sender->disconnect();
				delete socket_sender;
				string ip, port;
				bool split = false;
				for (size_t i = 0; i < answer.length(); i++)
				{
					if (!split) {
						split = (answer[i] == ':');
						if (split)continue;
						ip += answer[i];
					}
					else {
						port += answer[i];
					}
				}
				thread th(&MySocket::listener, *&socket_listener,
					ip,
					port);
				th.detach();
				socket_sender = new MySocket();
			}
			else {
				stopped = true;
				socket_listener->disconnect();
				delete socket_listener;
				socket_listener = nullptr;
				socket_sender->disconnect();
				delete socket_sender;
				socket_sender = nullptr;
				tbMsg->Enabled = false;
				tbAnswer->Enabled = false;
				tbContent->Enabled = false;
				tbIpServ->Enabled = true;
				tbPass->Enabled = true;
				tbPortServ->Enabled = true;
				tbLogin->Enabled = true;
				btnRegist->Enabled = true;
				btnAuth->Text = "Вход";
			}
		}
		bool clickDown = false;
		System::Void tbMsg_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == Keys::Enter) {
				if ((tbMsg->Text == String::Empty)||(clickDown))
				{
					tbMsg->Text = String::Empty;
					clickDown = true;
				}
				else {
					string answer = socket_sender->sender(
								marshal_as<string>(tbIpServ->Text), 
								marshal_as<string>(tbPortServ->Text), 
								marshal_as<string>(tbMsg->Text));
					tbAnswer->AppendText(marshal_as<String^>(answer + "\n"));
				}
			}
		}
		System::Void tbMsg_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == Keys::Enter) {
				clickDown = false;
				tbMsg->Text = String::Empty;
			}
		}
		
		 System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			 if (stopped)return;
			 if (socket_listener) {
				if (!socket_listener->msg.empty()) {
					tbContent->AppendText(marshal_as<String^>(socket_listener->msg)+ "\r\n");
					socket_listener->msg.clear();
				}
			}
		}
};
}
