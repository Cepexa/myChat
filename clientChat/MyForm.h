#pragma once
#include "Service.h"
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
			this->btnAuth->Location = System::Drawing::Point(332, 81);
			this->btnAuth->Margin = System::Windows::Forms::Padding(2);
			this->btnAuth->Name = L"btnAuth";
			this->btnAuth->Size = System::Drawing::Size(77, 24);
			this->btnAuth->TabIndex = 0;
			this->btnAuth->Text = L"Вход";
			this->btnAuth->UseVisualStyleBackColor = true;
			this->btnAuth->Click += gcnew System::EventHandler(this, &MyForm::btnAuth_Click);
			// 
			// tbLogin
			// 
			this->tbLogin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbLogin->Location = System::Drawing::Point(235, 34);
			this->tbLogin->Margin = System::Windows::Forms::Padding(2);
			this->tbLogin->Name = L"tbLogin";
			this->tbLogin->Size = System::Drawing::Size(176, 20);
			this->tbLogin->TabIndex = 1;
			this->tbLogin->Text = L"UserName";
			// 
			// tbPass
			// 
			this->tbPass->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPass->Location = System::Drawing::Point(235, 58);
			this->tbPass->Margin = System::Windows::Forms::Padding(2);
			this->tbPass->Name = L"tbPass";
			this->tbPass->PasswordChar = '*';
			this->tbPass->Size = System::Drawing::Size(176, 20);
			this->tbPass->TabIndex = 2;
			// 
			// btnRegist
			// 
			this->btnRegist->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnRegist->Location = System::Drawing::Point(235, 81);
			this->btnRegist->Margin = System::Windows::Forms::Padding(2);
			this->btnRegist->Name = L"btnRegist";
			this->btnRegist->Size = System::Drawing::Size(93, 23);
			this->btnRegist->TabIndex = 3;
			this->btnRegist->Text = L"Регистрация";
			this->btnRegist->UseVisualStyleBackColor = true;
			this->btnRegist->Visible = false;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(190, 38);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(38, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Логин";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(190, 62);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(45, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Пароль";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(190, 12);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Сервер";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(330, 12);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(30, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"порт";
			// 
			// tbIpServ
			// 
			this->tbIpServ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbIpServ->Location = System::Drawing::Point(235, 11);
			this->tbIpServ->Margin = System::Windows::Forms::Padding(2);
			this->tbIpServ->Name = L"tbIpServ";
			this->tbIpServ->Size = System::Drawing::Size(92, 20);
			this->tbIpServ->TabIndex = 5;
			this->tbIpServ->Text = L"172.23.25.184";
			// 
			// tbPortServ
			// 
			this->tbPortServ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPortServ->Location = System::Drawing::Point(364, 12);
			this->tbPortServ->Margin = System::Windows::Forms::Padding(2);
			this->tbPortServ->Name = L"tbPortServ";
			this->tbPortServ->Size = System::Drawing::Size(47, 20);
			this->tbPortServ->TabIndex = 5;
			this->tbPortServ->Text = L"5000";
			// 
			// tbMsg
			// 
			this->tbMsg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbMsg->Enabled = false;
			this->tbMsg->Location = System::Drawing::Point(0, 0);
			this->tbMsg->Margin = System::Windows::Forms::Padding(2);
			this->tbMsg->Multiline = true;
			this->tbMsg->Name = L"tbMsg";
			this->tbMsg->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbMsg->Size = System::Drawing::Size(264, 82);
			this->tbMsg->TabIndex = 7;
			this->tbMsg->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tbMsg_KeyDown);
			this->tbMsg->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tbMsg_KeyUp);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(2);
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
			this->splitContainer1->Size = System::Drawing::Size(264, 272);
			this->splitContainer1->SplitterDistance = 187;
			this->splitContainer1->SplitterWidth = 3;
			this->splitContainer1->TabIndex = 8;
			// 
			// tbContent
			// 
			this->tbContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbContent->Enabled = false;
			this->tbContent->Location = System::Drawing::Point(0, 0);
			this->tbContent->Margin = System::Windows::Forms::Padding(2);
			this->tbContent->Multiline = true;
			this->tbContent->Name = L"tbContent";
			this->tbContent->ReadOnly = true;
			this->tbContent->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbContent->Size = System::Drawing::Size(264, 187);
			this->tbContent->TabIndex = 9;
			// 
			// tbAnswer
			// 
			this->tbAnswer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbAnswer->Enabled = false;
			this->tbAnswer->Location = System::Drawing::Point(0, 0);
			this->tbAnswer->Margin = System::Windows::Forms::Padding(2);
			this->tbAnswer->Multiline = true;
			this->tbAnswer->Name = L"tbAnswer";
			this->tbAnswer->ReadOnly = true;
			this->tbAnswer->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbAnswer->Size = System::Drawing::Size(133, 272);
			this->tbAnswer->TabIndex = 9;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer2->Location = System::Drawing::Point(9, 109);
			this->splitContainer2->Margin = System::Windows::Forms::Padding(2);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->tbAnswer);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->splitContainer1);
			this->splitContainer2->Size = System::Drawing::Size(400, 272);
			this->splitContainer2->SplitterDistance = 133;
			this->splitContainer2->SplitterWidth = 3;
			this->splitContainer2->TabIndex = 10;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(421, 391);
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
			this->Margin = System::Windows::Forms::Padding(2);
			this->MinimumSize = System::Drawing::Size(259, 353);
			this->Name = L"MyForm";
			this->Text = L"Client";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
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
		ServiceClient* sClient;
		bool stopped = true;
		bool noClick = true; //пока не отработал полностью алгоритм кнопки запретить повторное нажатие
		System::Void btnAuth_Click(System::Object^ sender, System::EventArgs^ e) {
			if (noClick)
			{
				noClick = false;
				try {
				if (stopped) {
					on();
				}
				else {
					off();
				}
			}
			catch (const char* ex) {
				MessageBox::Show(marshal_as<String^>(ex) + "\r\n");
			}
			noClick = true;
			}
		}
		bool clickEnter = false;
		System::Void tbMsg_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if ((e->KeyCode == Keys::Enter)) {
				if (tbMsg->Text == "") clickEnter = true;
				if (clickEnter) {
					tbMsg->Clear();
				}
				else {
					clickEnter = true;
					sClient->SendMessage(marshal_as<string>(tbMsg->Text));
					tbContent->AppendText(Environment::NewLine + "Вы: " + tbMsg->Text);
					tbMsg->Clear();
				}
			}
		}
		System::Void tbMsg_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == Keys::Enter) {
				tbMsg->Clear();
				clickEnter = false;
			}
		}
		void on() {
			tbContent->Clear();
			sClient = new ServiceClient(
				marshal_as<string>(tbIpServ->Text),
				marshal_as<string>(tbPortServ->Text),
				marshal_as<string>(tbLogin->Text),
				marshal_as<string>(tbPass->Text));
			sClient->start();
			tbContent->AppendText("Добро пожаловать, " + 
									marshal_as<String^>(sClient->userName));
			changeVisibleFields(true);
			Threading::Thread^ th = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &MyForm::Receive));
			th->Start();
		}
		void off() {
			if (sClient != nullptr) {
				sClient->Disconnect();
				delete sClient;
				sClient = nullptr;
			}
			changeVisibleFields(false);
		}
		void changeVisibleFields(const bool &flag) {
			 tbMsg->Enabled = flag;
			 tbAnswer->Enabled = flag;
			 tbContent->Enabled = flag;
			 tbIpServ->Enabled = !flag;
			 tbPass->Enabled = !flag;
			 tbPortServ->Enabled = !flag;
			 tbLogin->Enabled = !flag;
			 btnRegist->Enabled = !flag;
			 (flag)?btnAuth->Text = "Выход": btnAuth->Text = "Вход";
			 stopped = !flag;
		 }
		void Receive()
		{
			 while (!stopped)
			 {
				 try
				 {
						 String^ vMsg = marshal_as<String^>(sClient->ReceiveMessage());
						 if (sClient == nullptr)return;
						 this->Invoke(gcnew Action<String^>(this, &MyForm::outText), vMsg);
						 if (vMsg == "Сервер остановлен!") {
							 this->Invoke(gcnew Action(this, &MyForm::off));
						 }
				 }
				 catch(...)
				 {
					 //соединение было прервано
					 if (stopped)return;
					 this->Invoke(gcnew Action<String^>(this, &MyForm::outText), "Подключение прервано!");
					 this->Invoke(gcnew Action(this, &MyForm::off));
				 }
			 }
		}
		void outText(String^ msg) {
			tbContent->AppendText(Environment::NewLine + msg);
		}
		System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (!stopped)off();
		}
};
}
