#include "CreateVectorLerpAction.h"
#include <Engine/Core/AssetLibrary/AssetLibrary.h>
#include <Engine/Core/Trigger/Trigger.h>


CreateVectorLerpAction::CreateVectorLerpAction(void)
{}
 

CreateVectorLerpAction::CreateVectorLerpAction(int32 _type): AbstractAction(_type)
{}



CreateVectorLerpAction::~CreateVectorLerpAction(void)
{
	Destroying();
}



void CreateVectorLerpAction::UpdateValid(void)
{
	valid = false; 

	if(arg.IsNotEmpty()) 
	{ 
		AssetLibrary::_GetAssets().Disconnect(AssetLibrary::CREATE_OBJECT_MESSAGE, this);
		valid = true;
	}
}


void CreateVectorLerpAction::SetVariableArg(int32 _index, StringANSI _name)
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
					if(object->IsClassPropertyExist(Variable<StringANSI>::STRING_VARIABLE_CLASS)) 
					{
						if(arg.Attach(dynamic_cast<Variable<StringANSI>*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ArgIsRenamed));
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


void CreateVectorLerpAction::SetTemplateArg(int32 _index, StringANSI _expr)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::TemplateArgIsCompleted));
			templateArg.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ArgIsLost));
			templateArg.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::TemplateArgIsChanged));
			
			SetArgMode(_index, TEMPLATE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			ArgIsLost(); 

			if(templateArg.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{ 
				TemplateArgIsCompleted();
			}
			break;
		} 
	}
}


void CreateVectorLerpAction::SetStringKeyArg(int32 _index, StringANSI _value)
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
			Variable<StringANSI>* object = new Variable<StringANSI>();
			object->SetValue(_value);
			
			if(arg.Attach(object))
			{
				UpdateValid();
			}
			break;
		}
	}
}



void CreateVectorLerpAction::TemplateArgIsCompleted(void)
{
	if(templateArg.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateArg.GetResult(), state[ASSET_TYPE][ARG1]) : AssetLibrary::_GetAssets().FindObject(templateArg.GetResult());

		if(arg.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(Variable<StringANSI>::STRING_VARIABLE_CLASS)) 
				{
					if(arg.Attach(dynamic_cast<Variable<StringANSI>*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}


void CreateVectorLerpAction::ArgIsLost(void)
{
	if(arg.IsNotEmpty())
	{ 
		arg.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		arg.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		arg.Clear();
		
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsCreated));
	valid = false;
}



void CreateVectorLerpAction::TemplateArgIsChanged(void)
{
	ArgIsLost();

	TemplateArgIsCompleted(); 
}




StringANSI CreateVectorLerpAction::GetTemplateArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return templateArg.GetStringExpr();
		}
	}
	return "";
}



StringANSI CreateVectorLerpAction::GetVariableArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return argName;
		}
	}
	return "";
}



StringANSI CreateVectorLerpAction::GetStringKeyArg(int32 _index)
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
	return "";
}



void CreateVectorLerpAction::operator () (void)
{
	if(IsValid())  
	{
		VectorLerp* vLerp = new VectorLerp();
		vLerp->Rename(arg.Get()->GetValue());
						
		if(!AssetLibrary::_GetAssets().AddObject(vLerp))
		{
			delete vLerp;
		}	
	}
}



void CreateVectorLerpAction::ObjectIsDestroyed(AbstractObject* _object)
{
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsCreated));
	valid = false;
}


 

void CreateVectorLerpAction::ArgIsRenamed(AbstractObject::NameInfo* _info)
{
	ArgIsLost();
}



void CreateVectorLerpAction::ObjectIsCreated(AbstractObject* _object)
{
	if(arg.IsEmpty())
	{ 
		if(state[TEMPLATE][ARG1])
		{
			if(_object->IsClassPropertyExist(Variable<StringANSI>::STRING_VARIABLE_CLASS))
			{
				if(templateArg.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateArg.GetResult() == _object->GetName())
				{
					if(arg.Attach(dynamic_cast<Variable<StringANSI>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		} 
		else if(state[VARIABLE][ARG1])
		{
			if(_object->IsClassPropertyExist(Variable<StringANSI>::STRING_VARIABLE_CLASS))
			{
				if(argName == _object->GetName())
				{
					if(arg.Attach(dynamic_cast<Variable<StringANSI>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &CreateVectorLerpAction::ArgIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}



bool CreateVectorLerpAction::SaveToFile(StringANSI _path)			
{
	if(_path.empty())
	{
		_path = AssetLibrary::_GetDir() + actionsDir + GetName() + "." + actionsSuffix;
	} 

	File file(_path, File::REWRITE);

	if(!SaveToFile(file))
	{
		file.Remove();
		return false;
	}
	return true; 
}


bool CreateVectorLerpAction::SaveToFile(File& _file)
{
	if(_file.IsOpened() && (_file.GetAccessMode() == File::WRITE || _file.GetAccessMode() == File::REWRITE))
	{
		_file.Write(type);
		_file.Write(GetName().length());
		_file.WriteString(GetName());
		for(int32 i = 0; i < AbstractAction::WIDTH; i++)
		{
			for(int32 j = 0; j < AbstractAction::HEIGHT; j++)
			{
				_file.Write(state[i][j]);
			}
		}
		_file.Write(activationLimit);
		_file.Write(loadArgsEnable);
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
			_file.Write(GetStringKeyArg(ARG1).length());
			_file.WriteString(GetStringKeyArg(ARG1));
		} 
		return true;
	}
	return false;
}


AbstractAction* CreateVectorLerpAction::_LoadFromFile(File& _file)
{
	CreateVectorLerpAction* action = new CreateVectorLerpAction(VectorLerp::CREATE_VECTOR_LERP_MESSAGE);
	StringANSI name;
	int32 length;
	_file.Read(length);
	_file.ReadString(name, length);  
	action->Rename(name);
	for(int32 i = 0; i < AbstractAction::WIDTH; i++)
	{
		for(int32 j = 0; j < AbstractAction::HEIGHT; j++)
		{
			_file.Read(action->state[i][j]);
		}
	}
	int32 activationLimit;
	_file.Read(activationLimit); 
	action->SetActivationLimit(activationLimit);
	bool loadArgsEnable;
	_file.Read(loadArgsEnable); 
	action->SetLoadArgsEnable(loadArgsEnable);
	if(action->state[TEMPLATE][ARG1])
	{
		StringANSI templateArg;
		_file.Read(length);
		_file.ReadString(templateArg, length);
		action->SetTemplateArg(ARG1, templateArg); 
	}
	else if(action->state[VARIABLE][ARG1])
	{
		StringANSI variableArg;
		_file.Read(length);
		_file.ReadString(variableArg, length);
		action->SetVariableArg(ARG1, variableArg);
	}
	else if(action->state[KEY][ARG1])
	{
		StringANSI arg; 
		_file.Read(length);
		_file.ReadString(arg, length);
		action->SetStringKeyArg(ARG1, arg);
	}
	return action;
}
