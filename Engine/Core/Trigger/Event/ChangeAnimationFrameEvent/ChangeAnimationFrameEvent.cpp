#include "ChangeAnimationFrameEvent.h"
#include <Engine/Core/AssetLibrary/AssetLibrary.h>
#include <Engine/Core/Trigger/Trigger.h>




ChangeAnimationFrameEvent::ChangeAnimationFrameEvent(void)
{}



ChangeAnimationFrameEvent::ChangeAnimationFrameEvent(int32 _type): AbstractEvent(_type)
{}



ChangeAnimationFrameEvent::~ChangeAnimationFrameEvent(void)
{
	Destroying();
}


void ChangeAnimationFrameEvent::UpdateValid(void)
{
	if((arg.IsNotEmpty() || !argsEnable) && source.IsNotEmpty()) 
	{ 
		AssetLibrary::_GetAssets().Disconnect(AssetLibrary::CREATE_OBJECT_MESSAGE, this);
	}
}




void ChangeAnimationFrameEvent::SetVariableArg(int32 _index, StringANSI _name)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateArg.Destroy();
			
			SetArgMode(_index, VARIABLE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			ArgIsLost(); 
			
			argName = _name;

			AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(argName, state[ASSET_TYPE][_index]) : AssetLibrary::_GetAssets().FindObject(argName);

			if(arg.IsEmpty())
			{ 
				if(object)
				{
					if(object->IsClassPropertyExist(Variable<int32>::INTEGER_VARIABLE_CLASS)) 
					{
						if(arg.Attach(dynamic_cast<Variable<int32>*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ArgIsRenamed));
							UpdateValid();
						}
						return;
					}
				}
			}
			break;
		}

		case SOURCE:
		{
			templateSource.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateSource.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateSource.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateSource.Destroy();
			
			SetArgMode(_index, VARIABLE);

			SourceIsLost();
  
			sourceName = _name;

			AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(sourceName, state[ASSET_TYPE][_index]) : AssetLibrary::_GetAssets().FindObject(sourceName);

			if(source.IsEmpty())
			{
				if(object)
				{ 
					if(object->IsClassPropertyExist(AbstractAnimation::ABSTRACT_ANIMATION_CLASS)) 
					{ 
						if(loadArgsEnable) { state[ASSET_TYPE][_index] = AssetLibrary::_GetAssetType(object->GetClassProperties()); }
						if(source.Attach(dynamic_cast<AbstractAnimation*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::SourceIsRenamed));
							object->Connect(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::EventHandler));
							UpdateValid();
						}
						return;
					}
				}
			}
			break;
		}
	}
}


void ChangeAnimationFrameEvent::SetTemplateArg(int32 _index, StringANSI _expr)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::TemplateArgIsCompleted));
			templateArg.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ArgIsLost));
			templateArg.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::TemplateArgIsChanged));
			
			SetArgMode(_index, TEMPLATE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			ArgIsLost(); 

			if(templateArg.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{ 
				TemplateArgIsCompleted();
			}
			break;
		}  

		case SOURCE:
		{
			templateSource.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::TemplateSourceIsCompleted));
			templateSource.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::SourceIsLost));
			templateSource.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::TemplateSourceIsChanged));
			
			SetArgMode(_index, TEMPLATE);

			SourceIsLost(); 

			if(templateSource.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{
				TemplateSourceIsCompleted();
			}
			break;
		}
	}
}



void ChangeAnimationFrameEvent::SetIntegerKeyArg(int32 _index, int32 _value)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateArg.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateArg.Destroy();
			
			SetArgMode(_index, KEY);

			ArgIsLost();
			Variable<int32>* object = new Variable<int32>();
			object->SetValue(_value);
			
			if(arg.Attach(object))
			{
				UpdateValid();
			}
			break;
		}
	}
}



void ChangeAnimationFrameEvent::TemplateArgIsCompleted(void)
{
	if(templateArg.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateArg.GetResult(), state[ASSET_TYPE][ARG1]) : AssetLibrary::_GetAssets().FindObject(templateArg.GetResult());

		if(arg.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(Variable<int32>::INTEGER_VARIABLE_CLASS)) 
				{
					if(arg.Attach(dynamic_cast<Variable<int32>*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}


void ChangeAnimationFrameEvent::ArgIsLost(void)
{
	if(arg.IsNotEmpty())
	{
		arg.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		arg.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		arg.Clear();
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsCreated));
}



void ChangeAnimationFrameEvent::TemplateArgIsChanged(void)
{
	ArgIsLost();

	TemplateArgIsCompleted(); 
}




void ChangeAnimationFrameEvent::TemplateSourceIsCompleted(void)
{
	if(templateSource.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateSource.GetResult(), state[ASSET_TYPE][SOURCE]) : AssetLibrary::_GetAssets().FindObject(templateSource.GetResult());

		if(source.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(AbstractAnimation::ABSTRACT_ANIMATION_CLASS)) 
				{ 
					if(loadArgsEnable) { state[ASSET_TYPE][SOURCE] = AssetLibrary::_GetAssetType(object->GetClassProperties()); }
					if(source.Attach(dynamic_cast<AbstractAnimation*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::SourceIsRenamed));
						object->Connect(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::EventHandler));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}


void ChangeAnimationFrameEvent::SourceIsLost(void)
{
	if(source.IsNotEmpty())
	{
		source.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		source.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		source.Get()->Disconnect(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE, this);
		source.Clear();
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsCreated));
}



void ChangeAnimationFrameEvent::TemplateSourceIsChanged(void)
{
	SourceIsLost();

	TemplateSourceIsCompleted(); 
}





StringANSI ChangeAnimationFrameEvent::GetTemplateArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return templateArg.GetStringExpr();
		}

		case SOURCE:
		{
			return templateSource.GetStringExpr();
		}
	}
	return "";
}



int32 ChangeAnimationFrameEvent::GetIntegerKeyArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			if(arg.IsNotEmpty())
			{
				return arg.Get()->GetValue();
			}
		}
	}
	return -1;
}



StringANSI ChangeAnimationFrameEvent::GetVariableArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return argName;
		}

		case SOURCE:
		{
			return sourceName;
		}
	}
	return "";
}


void ChangeAnimationFrameEvent::SetValue(bool _value)
{
	AbstractEvent::SetValue(_value);

	if(_value)
	{
		if(deactivationMode == AbstractEvent::AUTO_SWITCH_OFF) 
		{ 
			SetValue(false); 
		}
	}
}


void ChangeAnimationFrameEvent::EventHandler(int32 _value)
{
	if(argsEnable)
	{
		if(arg.IsNotEmpty())
		{ 
			if(arg.Get()->GetValue() == _value)
			{ 
				SetValue(true);
			}
			else if(arg.Get()->GetValue() == -1 && source.Get()->IsLastFrame())
			{
				SetValue(true);
			}
			else if(deactivationMode == AbstractEvent::OVERLAY_SWITCH_OFF)
			{
				SetValue(false);
			} 
		}
	}
	else
	{
		SetValue(true);
	}
}


void ChangeAnimationFrameEvent::ObjectIsDestroyed(AbstractObject* _object)
{
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsCreated));
}


void ChangeAnimationFrameEvent::SourceIsRenamed(AbstractObject::NameInfo* _info)
{
	SourceIsLost();
}
 


void ChangeAnimationFrameEvent::ArgIsRenamed(AbstractObject::NameInfo* _info)
{
	ArgIsLost();
}


void ChangeAnimationFrameEvent::ObjectIsCreated(AbstractObject* _object)
{
	if(source.IsEmpty())
	{
		if(state[TEMPLATE][SOURCE])
		{
			if(_object->IsClassPropertyExist(AbstractAnimation::ABSTRACT_ANIMATION_CLASS)) 
			{
				if(templateSource.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateSource.GetResult() == _object->GetName())
				{ 
					if(loadArgsEnable) { state[ASSET_TYPE][SOURCE] = AssetLibrary::_GetAssetType(_object->GetClassProperties()); }
					if(source.Attach(dynamic_cast<AbstractAnimation*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::SourceIsRenamed));
						_object->Connect(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::EventHandler));
						UpdateValid();
					}
					return;
				}
			}
		}
		else if(state[VARIABLE][SOURCE])
		{
			if(_object->IsClassPropertyExist(AbstractAnimation::ABSTRACT_ANIMATION_CLASS)) 
			{
				if(sourceName == _object->GetName())
				{
					if(loadArgsEnable) { state[ASSET_TYPE][SOURCE] = AssetLibrary::_GetAssetType(_object->GetClassProperties()); }
					if(source.Attach(dynamic_cast<AbstractAnimation*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::SourceIsRenamed));
						_object->Connect(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::EventHandler));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
	if(arg.IsEmpty())
	{ 
		if(state[TEMPLATE][ARG1])
		{
			if(_object->IsClassPropertyExist(Variable<int32>::INTEGER_VARIABLE_CLASS)) 
			{
				if(templateArg.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateArg.GetResult() == _object->GetName())
				{
					if(arg.Attach(dynamic_cast<Variable<int32>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		} 
		else if(state[VARIABLE][ARG1])
		{
			if(_object->IsClassPropertyExist(Variable<int32>::INTEGER_VARIABLE_CLASS)) 
			{
				if(argName == _object->GetName())
				{
					if(arg.Attach(dynamic_cast<Variable<int32>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &ChangeAnimationFrameEvent::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}



bool ChangeAnimationFrameEvent::SaveToFile(StringANSI _path)			
{
	if(_path.empty())
	{
		_path = AssetLibrary::_GetDir() + eventsDir + GetName() + "." + eventsSuffix;
	} 
 
	File file(_path, File::REWRITE);

	if(!SaveToFile(file))
	{
		file.Remove();
		return false;
	}
	return true; 
}


bool ChangeAnimationFrameEvent::SaveToFile(File& _file)
{
	if(_file.IsOpened() && (_file.GetAccessMode() == File::WRITE || _file.GetAccessMode() == File::REWRITE))
	{
		_file.Write(type);
		_file.Write(GetName().length());
		_file.WriteString(GetName());
		for(int32 i = 0; i < AbstractEvent::WIDTH; i++)
		{
			for(int32 j = 0; j < AbstractEvent::HEIGHT; j++)
			{
				_file.Write(state[i][j]);
			}
		}
		_file.Write(activationLimit);
		_file.Write(loadArgsEnable);
		_file.Write(deactivationMode);
		_file.Write(argsEnable);
		_file.Write(value);
		if(state[TEMPLATE][ARG1])
		{
			_file.Write(GetTemplateArg(ARG1).length());
			_file.WriteString(GetTemplateArg(ARG1));
		}
		else if(state[VARIABLE][ARG1])
		{
			_file.Write(GetVariableArg(ARG1).length());
			_file.WriteString(GetVariableArg(ARG1));
		}
		else if(state[KEY][ARG1])
		{
			_file.Write(GetIntegerKeyArg(ARG1));
		}
		if(state[TEMPLATE][SOURCE])
		{
			_file.Write(GetTemplateArg(SOURCE).length());
			_file.WriteString(GetTemplateArg(SOURCE));
		}
		else if(state[VARIABLE][SOURCE])
		{
			_file.Write(GetVariableArg(SOURCE).length());
			_file.WriteString(GetVariableArg(SOURCE));
		} 
		return true;
	}
	return false;
}


AbstractEvent* ChangeAnimationFrameEvent::_LoadFromFile(File& _file)
{
	ChangeAnimationFrameEvent* event = new ChangeAnimationFrameEvent(AbstractAnimation::CHANGE_ANIMATION_FRAME_MESSAGE);
	StringANSI name;
	int32 length;
	_file.Read(length);
	_file.ReadString(name, length);
	event->Rename(name);
	for(int32 i = 0; i < AbstractEvent::WIDTH; i++)
	{
		for(int32 j = 0; j < AbstractEvent::HEIGHT; j++)
		{
			_file.Read(event->state[i][j]);
		}
	}
	int32 activationLimit;
	_file.Read(activationLimit); 
	event->SetActivationLimit(activationLimit);
	bool loadArgsEnable;
	_file.Read(loadArgsEnable); 
	event->SetLoadArgsEnable(loadArgsEnable);
	int32 deactivationMode;
	_file.Read(deactivationMode);
	event->SetDeactivationMode(deactivationMode);
	bool argsEnable;
	_file.Read(argsEnable);
	event->SetArgsEnable(argsEnable);
	bool value;
	_file.Read(value);
	if(event->state[TEMPLATE][ARG1])
	{
		StringANSI templateArg;
		_file.Read(length);
		_file.ReadString(templateArg, length);
		event->SetTemplateArg(ARG1, templateArg); 
	}
	else if(event->state[VARIABLE][ARG1])
	{
		StringANSI variableArg;
		_file.Read(length);
		_file.ReadString(variableArg, length);
		event->SetVariableArg(ARG1, variableArg);
	}
	else if(event->state[KEY][ARG1])
	{
		int32 arg; 
		_file.Read(arg); 
		event->SetIntegerKeyArg(ARG1, arg);
	}
	if(event->state[TEMPLATE][SOURCE])
	{
		StringANSI templateArg;
		_file.Read(length);
		_file.ReadString(templateArg, length);
		event->SetTemplateArg(SOURCE, templateArg); 
	}
	else if(event->state[VARIABLE][SOURCE])
	{
		StringANSI variableArg;
		_file.Read(length);
		_file.ReadString(variableArg, length);
		event->SetVariableArg(SOURCE, variableArg);
	}

	if(value) { event->value = value; }
	return event;
}