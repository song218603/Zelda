// Zelda Games


#include "ZeldaGameInstance.h"
#include "HttpModule.h"
#include "Http.h"


void UZeldaGameInstance::Init()
{
	Super::Init();
}

void UZeldaGameInstance::Tick(float DeltaTime)
{
	
}

TStatId UZeldaGameInstance::GetStatId() const
{
	return TStatId();
}

void UZeldaGameInstance::Shutdown()
{
	Super::Shutdown();
	
	// TODO
}

void UZeldaGameInstance::Login(FString InUsername, FString InPassword)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://62.234.41.215:8000/login"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// 构造 JSON
	TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
	RequestObj->SetStringField(TEXT("username"), InUsername);
	RequestObj->SetStringField(TEXT("password"), InPassword);

	FString JsonBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer);

	Request->SetContentAsString(JsonBody);
	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnLoginResponseReceived);
	Request->ProcessRequest();
}

void UZeldaGameInstance::OnLoginResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	ELoginResult FinalResult = ELoginResult::NetworkError;

	if (bWasSuccessful && Response.IsValid())
	{
		int32 Code = Response->GetResponseCode();
		if (Code == 200)
		{
			// 获取 JSON 字符串
			FString ResponseBody = Response->GetContentAsString();
            
			// 创建 JsonReader
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

			// 反序列化
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				// 提取基础字段
				Username = JsonObject->GetStringField(TEXT("username"));

				// 提取嵌套的 meta 对象
				const TSharedPtr<FJsonObject>* MetaObject;
				if (JsonObject->TryGetObjectField(TEXT("meta"), MetaObject))
				{
					Health = (*MetaObject)->GetIntegerField(TEXT("health"));
					Energy = (*MetaObject)->GetIntegerField(TEXT("energy"));
				}

				FinalResult = ELoginResult::Success;
				// 设置心跳
				GetWorld()->GetTimerManager().SetTimer(HeartbeatTimerHandle, this, &ThisClass::SendHeartbeat, 1.0f, true);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("JSON 解析失败！内容: %s"), *ResponseBody);
				FinalResult = ELoginResult::NetworkError;
			}
		}
		else if (Code == 401) FinalResult = ELoginResult::WrongPass;
		else if (Code == 404) FinalResult = ELoginResult::NoUser;
	}

	// 执行委托，通知所有绑定的 UI
	OnLoginFinished.Broadcast(FinalResult);
}

void UZeldaGameInstance::SendHeartbeat() const
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	// 这里的 username 是你登录成功后保存的 CurrentUsername
	Request->SetURL(FString::Printf(TEXT("http://62.234.41.215:8000/heartbeat?username=%s"), *Username));
	Request->SetVerb(TEXT("POST"));
	Request->ProcessRequest();
}
