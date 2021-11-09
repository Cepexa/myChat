#pragma once

#include "ServerObject.h"
#include "Socket.h"
namespace BackEnd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// <summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			msg = new string();
			showListIpAdd();
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
	private: System::Windows::Forms::ComboBox^ cbIp;
	protected:
	private: System::Windows::Forms::TextBox^ tbPort;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::ListBox^ lbClient;

	private: System::Windows::Forms::SplitContainer^ splitContainer1;

	private: System::Windows::Forms::TextBox^ tbContent;
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
			this->cbIp = (gcnew System::Windows::Forms::ComboBox());
			this->tbPort = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->lbClient = (gcnew System::Windows::Forms::ListBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->tbContent = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbIp
			// 
			this->cbIp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->cbIp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbIp->FormattingEnabled = true;
			this->cbIp->Location = System::Drawing::Point(28, 11);
			this->cbIp->Margin = System::Windows::Forms::Padding(2);
			this->cbIp->Name = L"cbIp";
			this->cbIp->Size = System::Drawing::Size(132, 21);
			this->cbIp->TabIndex = 0;
			this->cbIp->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::cbIp_MouseClick);
			// 
			// tbPort
			// 
			this->tbPort->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPort->Location = System::Drawing::Point(194, 11);
			this->tbPort->Margin = System::Windows::Forms::Padding(2);
			this->tbPort->MaxLength = 5;
			this->tbPort->Name = L"tbPort";
			this->tbPort->Size = System::Drawing::Size(67, 20);
			this->tbPort->TabIndex = 1;
			this->tbPort->Text = L"5000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 14);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ip";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(165, 14);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"port";
			// 
			// btnStart
			// 
			this->btnStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnStart->Location = System::Drawing::Point(89, 40);
			this->btnStart->Margin = System::Windows::Forms::Padding(2);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(88, 46);
			this->btnStart->TabIndex = 3;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// lbClient
			// 
			this->lbClient->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbClient->FormattingEnabled = true;
			this->lbClient->Location = System::Drawing::Point(0, 0);
			this->lbClient->Margin = System::Windows::Forms::Padding(2);
			this->lbClient->Name = L"lbClient";
			this->lbClient->Size = System::Drawing::Size(69, 192);
			this->lbClient->TabIndex = 4;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->Location = System::Drawing::Point(9, 98);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(2);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->lbClient);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->tbContent);
			this->splitContainer1->Size = System::Drawing::Size(249, 192);
			this->splitContainer1->SplitterDistance = 69;
			this->splitContainer1->SplitterWidth = 3;
			this->splitContainer1->TabIndex = 6;
			// 
			// tbContent
			// 
			this->tbContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbContent->Location = System::Drawing::Point(0, 0);
			this->tbContent->Multiline = true;
			this->tbContent->Name = L"tbContent";
			this->tbContent->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbContent->Size = System::Drawing::Size(177, 192);
			this->tbContent->TabIndex = 7;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(273, 318);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbPort);
			this->Controls->Add(this->cbIp);
			this->Margin = System::Windows::Forms::Padding(2);
			this->MinimumSize = System::Drawing::Size(289, 357);
			this->Name = L"MyForm";
			this->Text = L"Server";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		ServerObject* server;
		bool stopped = true;
		string* msg;
		//ServerObject server; // сервер
		System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (stopped) {
				stopped = false;
				btnStart->Text = "Стоп";
				try{
					on();
				}
				catch (const exception& ex)
				{
					off();
					tbContent->AppendText(marshal_as <String^>(ex.what()));
				}
			}
			else {
				off();
			}
		}
		System::Void cbIp_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			showListIpAdd();
		}
		void outText(String^ msg) {
					tbContent->AppendText(msg + "\r\n");
		}
		void recvMsg() {
			try {
			do {
				if (!msg->empty()) {
					try {
						String^ vMsg = marshal_as<String^>(*msg);
						this->Invoke(gcnew Action<String^>(this, &MyForm::outText), vMsg);
						msg->clear();
					}
					catch (...) {}
				}
			} while (!stopped);
			}
			catch (...) {}
		}
		void on() {
			server = new ServerObject();
			thread listenThread(&ServerObject::Listen, *&server,
				marshal_as <string>(cbIp->Text),
				marshal_as <string>(tbPort->Text),
				ref(*msg));//старт потока
			listenThread.detach();
			Threading::Thread^ th = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &MyForm::recvMsg));
			th->Start();
		}
		void off() {
			server->Disconnect();
			delete server;
			btnStart->Text = "Старт";
			stopped = true;
		}
		void showListIpAdd() {
			size_t sz = 0;
			string* addrs = getListIpAdd(sz);
			cbIp->Items->Clear();
			for (size_t i = 0; i < sz; i++)
			{
				cbIp->Items->Add(marshal_as<String^>(addrs[i]));
			}
			if (sz != 0) {
				cbIp->Text = cbIp->Items[0]->ToString();
			}
		}
		string* getListIpAdd(size_t& size) {
			const int WSVer = 0x101;
			WSAData wsaData;
			string* str = nullptr;
			hostent* h;
			char Buf[128];
			if (WSAStartup(WSVer, &wsaData) == 0)
			{
				if (gethostname(&Buf[0], 128) == 0)
				{
					h = gethostbyname(&Buf[0]);
					size = h->h_addrtype;
					str = new string[size];
					for (size_t i = 0; i < size; i++)
					{
						str[i] = inet_ntoa(*(reinterpret_cast<in_addr*>(h->h_addr_list[i])));
					}
				}
				WSACleanup();
			}
			return str;
		}
	System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		if(!stopped)off();
	}
};
}
