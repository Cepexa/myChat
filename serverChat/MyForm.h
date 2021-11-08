#pragma once

#include "../ddlSocket/Socket.h"

namespace serverChat {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
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
			stopped = true;
			int sz=0;
			string* addrs = getListIpAdd(sz);
			for (size_t i = 0; i < sz; i++)
			{
				cbIp->Items->Add(marshal_as<String^>(addrs[i]));
			}
			if (sz != 0) {
				cbIp->Text = cbIp->Items[0]->ToString();
			}
			clients = new vector<Client*>;

		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
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
	private: System::Windows::Forms::ListBox^ lbContent;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->cbIp = (gcnew System::Windows::Forms::ComboBox());
			this->tbPort = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->lbClient = (gcnew System::Windows::Forms::ListBox());
			this->lbContent = (gcnew System::Windows::Forms::ListBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
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
			this->cbIp->Location = System::Drawing::Point(37, 14);
			this->cbIp->Name = L"cbIp";
			this->cbIp->Size = System::Drawing::Size(175, 24);
			this->cbIp->TabIndex = 0;
			// 
			// tbPort
			// 
			this->tbPort->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tbPort->Location = System::Drawing::Point(259, 14);
			this->tbPort->MaxLength = 5;
			this->tbPort->Name = L"tbPort";
			this->tbPort->Size = System::Drawing::Size(88, 22);
			this->tbPort->TabIndex = 1;
			this->tbPort->Text = L"5000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(19, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ip";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(220, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"port";
			// 
			// btnStart
			// 
			this->btnStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnStart->Location = System::Drawing::Point(119, 49);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(117, 56);
			this->btnStart->TabIndex = 3;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// lbClient
			// 
			this->lbClient->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbClient->FormattingEnabled = true;
			this->lbClient->ItemHeight = 16;
			this->lbClient->Location = System::Drawing::Point(0, 0);
			this->lbClient->Name = L"lbClient";
			this->lbClient->Size = System::Drawing::Size(93, 236);
			this->lbClient->TabIndex = 4;
			// 
			// lbContent
			// 
			this->lbContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbContent->FormattingEnabled = true;
			this->lbContent->ItemHeight = 16;
			this->lbContent->Location = System::Drawing::Point(0, 0);
			this->lbContent->Name = L"lbContent";
			this->lbContent->Size = System::Drawing::Size(235, 236);
			this->lbContent->TabIndex = 5;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->Location = System::Drawing::Point(12, 121);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->lbClient);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->lbContent);
			this->splitContainer1->Size = System::Drawing::Size(332, 236);
			this->splitContainer1->SplitterDistance = 93;
			this->splitContainer1->TabIndex = 6;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(362, 383);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbPort);
			this->Controls->Add(this->cbIp);
			this->MinimumSize = System::Drawing::Size(380, 430);
			this->Name = L"MyForm";
			this->Text = L"Server";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		vector<Client*>*clients;
		MySocket* socket_listener;
		MySocket* socket_sender;
		bool stopped;
		System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e)
		{
			try {
				if (stopped) {
					socket_listener = new MySocket();
					socket_sender = new MySocket();
					thread t1(&MySocket::listener, *&socket_listener, marshal_as<string>(cbIp->Text), marshal_as<string>(tbPort->Text));
					t1.detach();
					stopped = false;
					btnStart->Text = "Stop";
				}
				else {
					stopped = true;
					socket_listener->disconnect();
					delete socket_listener;
					socket_listener = nullptr;
					socket_sender->disconnect();
					delete socket_sender;
					socket_sender = nullptr;
					btnStart->Text = "Start";
				}

			}
			catch (char* ex) {
				MessageBox::Show(marshal_as<String^>(ex));
			}
		}
		string* getListIpAdd(int& size) {
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
				WSACleanup;
			}
			return str;
		} 
		System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (!stopped) {
				socket_listener->disconnect();
			}
		}
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			if (stopped)return;
			if (socket_listener) {
				if (!socket_listener->msg.empty()) {
					auto newClient = new Client("user", "", socket_listener->ipSocket, socket_listener->portSocket);

					clients->push_back(newClient);
					for (auto client : *clients)
					{
						if (client->id != 2)//заглушка до парсераq
						{
							socket_sender->sender(client->ip, marshal_as<string>(client->port.ToString()) ,socket_listener->msg);
						}
					}
					socket_listener->msg.clear();
				}
			}
		}
};
}
