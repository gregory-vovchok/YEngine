#include "Vector2ToSphericalAction.h"
#include <Engine/Core/AssetLibrary/AssetLibrary.h>
#include <Engine/Core/Trigger/Trigger.h>
#include <Engine/Core/Parser/List/AbstractObjectList/AbstractObjectList.h>




Vector2ToSphericalAction::Vector2ToSphericalAction(void)
{}


Vector2ToSphericalAction::Vector2ToSphericalAction(int32 _type): AbstractAction(_type)
{}



Vector2ToSphericalAction::~Vector2ToSphericalAction(void)
{
	Destroying();
}


void Vector2ToSphericalAction::UpdateValid(void)
{
	valid = false; 

	if(target.IsNotEmpty()) 
	{ 
		AssetLibrary::_GetAssets().Disconnect(AssetLibrary::CREATE_OBJECT_MESSAGE, this);
		valid = true;
	}
}

void Vector2ToSphericalAction::SetVariableArg(int32 _index, StringANSI _name)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg1.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateArg1.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateArg1.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateArg1.Destroy();
			
			SetArgMode(_index, VARIABLE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			Arg1IsLost(); 
			
			arg1Name = _name;

			AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(arg1Name, state[ASSET_TYPE][_index]) : AssetLibrary::_GetAssets().FindObject(arg1Name);

			if(arg1.IsEmpty())
			{
				if(object)
				{
					if(object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
					{
						if(arg1.Attach(dynamic_cast<Variable<float>*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg1IsRenamed));
							UpdateValid();
						}
						return;
					}
				}
			}
			break;
		}

		case ARG2:
		{
			templateArg2.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateArg2.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateArg2.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateArg2.Destroy();
			
			SetArgMode(_index, VARIABLE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			Arg2IsLost(); 
			
			arg2Name = _name;

			AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(arg2Name, state[ASSET_TYPE][_index]) : AssetLibrary::_GetAssets().FindObject(arg2Name);

			if(arg2.IsEmpty())
			{
				if(object)
				{
					if(object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
					{
						if(arg2.Attach(dynamic_cast<Variable<float>*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg2IsRenamed));
							UpdateValid();
						}
						return;
					}
				}
			}
			break;
		}

		case TARGET:
		{  
			templateTarget.Disconnect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this);
			templateTarget.Disconnect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this);
			templateTarget.Disconnect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this);
			templateTarget.Destroy();
			
			SetArgMode(_index, VARIABLE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			TargetIsLost();
  
			targetName = _name;

			AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(targetName, state[ASSET_TYPE][_index]) : AssetLibrary::_GetAssets().FindObject(targetName);

			if(target.IsEmpty())
			{
				if(object)
				{
					if(object->IsClassPropertyExist(Variable<Vector2>::VECTOR_2_VARIABLE_CLASS)) 
					{
						if(target.Attach(dynamic_cast<Variable<Vector2>*>(object)))
						{
							object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
							object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TargetIsRenamed));
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


void Vector2ToSphericalAction::SetTemplateArg(int32 _index, StringANSI _expr)
{
	switch(_index)
	{
		case ARG1:
		{
			templateArg1.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateArg1IsCompleted));
			templateArg1.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg1IsLost));
			templateArg1.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateArg1IsChanged));
			
			SetArgMode(_index, TEMPLATE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			Arg1IsLost(); 

			if(templateArg1.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{ 
				TemplateArg1IsCompleted();
			}
			break;
		}  

		case ARG2:
		{ 
			templateArg2.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateArg2IsCompleted));
			templateArg2.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg2IsLost));
			templateArg2.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateArg2IsChanged));
			
			SetArgMode(_index, TEMPLATE);
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			Arg2IsLost(); 

			if(templateArg2.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{ 
				TemplateArg2IsCompleted();
			}
			break;
		}  

		case TARGET:
		{
			templateTarget.Connect(StringExprParserEx::STRING_EXPR_COMPLETED_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateTargetIsCompleted));
			templateTarget.Connect(StringExprParserEx::STRING_EXPR_VARIABLE_LOSS_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TargetIsLost));
			templateTarget.Connect(StringExprParserEx::STRING_EXPR_CHANGE_VALUE_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TemplateTargetIsChanged));
			
			SetArgMode(_index, TEMPLATE);  
			state[ASSET_TYPE][_index] = AssetLibrary::VARIABLE_ASSET;

			TargetIsLost(); 

			if(templateTarget.Parse(_expr) == StringExprParserEx::NO_ERRORS)
			{
				TemplateTargetIsCompleted();
			}
			break;
		}
	}
}



void Vector2ToSphericalAction::TemplateArg1IsCompleted(void)
{
	if(templateArg1.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateArg1.GetResult(), state[ASSET_TYPE][ARG1]) : AssetLibrary::_GetAssets().FindObject(templateArg1.GetResult());

		if(arg1.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS)) 
				{
					if(arg1.Attach(dynamic_cast<Variable<float>*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg1IsRenamed));
						UpdateValid();
					}
					return;
				} 
			}
		}
	}
}


void Vector2ToSphericalAction::Arg1IsLost(void)
{
	if(arg1.IsNotEmpty())
	{ 
		arg1.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		arg1.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		arg1.Clear();
		
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsCreated));
	valid = false;
}



void Vector2ToSphericalAction::TemplateArg1IsChanged(void)
{
	Arg1IsLost();

	TemplateArg1IsCompleted(); 
}



void Vector2ToSphericalAction::TemplateArg2IsCompleted(void)
{
	if(templateArg2.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateArg2.GetResult(), state[ASSET_TYPE][ARG2]) : AssetLibrary::_GetAssets().FindObject(templateArg2.GetResult());

		if(arg2.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS)) 
				{
					if(arg2.Attach(dynamic_cast<Variable<float>*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg2IsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}



void Vector2ToSphericalAction::Arg2IsLost(void)
{
	if(arg2.IsNotEmpty())
	{ 
		arg2.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		arg2.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		arg2.Clear();
		
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsCreated));
	valid = false;
}



void Vector2ToSphericalAction::TemplateArg2IsChanged(void)
{
	Arg2IsLost();

	TemplateArg2IsCompleted(); 
}




void Vector2ToSphericalAction::TemplateTargetIsCompleted(void)
{
	if(templateTarget.Calculate() == StringExprParserEx::NO_ERRORS)
	{
		AbstractObject* object = loadArgsEnable ? AssetLibrary::_LoadCommonAsset(templateTarget.GetResult(), state[ASSET_TYPE][TARGET]) : AssetLibrary::_GetAssets().FindObject(templateTarget.GetResult());

		if(target.IsEmpty())
		{
			if(object)
			{
				if(object->IsClassPropertyExist(Variable<Vector2>::VECTOR_2_VARIABLE_CLASS)) 
				{
					if(target.Attach(dynamic_cast<Variable<Vector2>*>(object)))
					{
						object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TargetIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}



void Vector2ToSphericalAction::TargetIsLost(void)
{
	if(target.IsNotEmpty())
	{
		target.Get()->Disconnect(AbstractObject::DESTROY_OBJECT_MESSAGE, this);
		target.Get()->Disconnect(AbstractObject::CHANGE_NAME_MESSAGE, this);
		target.Clear();
	}
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsCreated));
	valid = false;
}



void Vector2ToSphericalAction::TemplateTargetIsChanged(void)
{
	TargetIsLost();

	TemplateTargetIsCompleted(); 
}



StringANSI Vector2ToSphericalAction::GetTemplateArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return templateArg1.GetStringExpr();
		}

		case ARG2:
		{
			return templateArg2.GetStringExpr();
		}

		case TARGET:
		{
			return templateTarget.GetStringExpr();
		}
	}
	return "";
}



StringANSI Vector2ToSphericalAction::GetVariableArg(int32 _index)
{
	switch(_index)
	{
		case ARG1:
		{
			return arg1Name;
		}

		case ARG2:
		{
			return arg2Name;
		}

		case TARGET:
		{
			return targetName;
		}
	}
	return "";
}



void Vector2ToSphericalAction::operator () (void)
{
	if(IsValid())
	{
		Vector2 polar = target.Get()->GetValue().ToPolar();
	
		if(arg1.IsNotEmpty()) { arg1.Get()->SetValue(polar.x); } 
		if(arg2.IsNotEmpty()) { arg2.Get()->SetValue(polar.y); }
	}
}



void Vector2ToSphericalAction::ObjectIsDestroyed(AbstractObject* _object)
{
	AssetLibrary::_GetAssets().Connect(AssetLibrary::CREATE_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsCreated));
	valid = false;
}



void Vector2ToSphericalAction::TargetIsRenamed(AbstractObject::NameInfo* _info)
{
	TargetIsLost();
}

 

void Vector2ToSphericalAction::Arg1IsRenamed(AbstractObject::NameInfo* _info)
{
	Arg1IsLost();
}


void Vector2ToSphericalAction::Arg2IsRenamed(AbstractObject::NameInfo* _info)
{
	Arg2IsLost();
}



void Vector2ToSphericalAction::ObjectIsCreated(AbstractObject* _object)
{
	if(target.IsEmpty())
	{
		if(state[TEMPLATE][TARGET])
		{
			if(_object->IsClassPropertyExist(Variable<Vector2>::VECTOR_2_VARIABLE_CLASS)) 
			{ 
				if(templateTarget.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateTarget.GetResult() == _object->GetName())
				{
					if(target.Attach(dynamic_cast<Variable<Vector2>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TargetIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
		else if(state[VARIABLE][TARGET])
		{
			if(_object->IsClassPropertyExist(Variable<Vector2>::VECTOR_2_VARIABLE_CLASS)) 
			{
				if(targetName == _object->GetName())
				{
					if(target.Attach(dynamic_cast<Variable<Vector2>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::TargetIsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
	if(arg1.IsEmpty())
	{ 
		if(state[TEMPLATE][ARG1])
		{
			if(_object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
			{
				if(templateArg1.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateArg1.GetResult() == _object->GetName())
				{
					if(arg1.Attach(dynamic_cast<Variable<float>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg1IsRenamed));
						UpdateValid();
					}
					return; 
				} 
			}
		} 
		else if(state[VARIABLE][ARG1])
		{ 
			if(_object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
			{
				if(arg1Name == _object->GetName())
				{
					if(arg1.Attach(dynamic_cast<Variable<float>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg1IsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
	if(arg2.IsEmpty())
	{ 
		if(state[TEMPLATE][ARG2])
		{
			if(_object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
			{
				if(templateArg2.GetCurrentError() == StringExprParserEx::NO_ERRORS && templateArg2.GetResult() == _object->GetName())
				{
					if(arg2.Attach(dynamic_cast<Variable<float>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg2IsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		} 
		else if(state[VARIABLE][ARG2])
		{
			if(_object->IsClassPropertyExist(Variable<float>::FLOAT_VARIABLE_CLASS))
			{
				if(arg2Name == _object->GetName())
				{
					if(arg2.Attach(dynamic_cast<Variable<float>*>(_object)))
					{
						_object->Connect(AbstractObject::DESTROY_OBJECT_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::ObjectIsDestroyed));
						_object->Connect(AbstractObject::CHANGE_NAME_MESSAGE, this, Caller<>(this, &Vector2ToSphericalAction::Arg2IsRenamed));
						UpdateValid();
					}
					return;
				}
			}
		}
	}
}



bool Vector2ToSphericalAction::SaveToFile(StringANSI _path)			
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


bool Vector2ToSphericalAction::SaveToFile(File& _file)
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
		if(state[TEMPLATE][ARG2])
		{
			_file.Write(GetTemplateArg(ARG2).length());
			_file.WriteString(GetTemplateArg(ARG2));
		}
		else if(state[VARIABLE][ARG2])
		{
			_file.Write(GetVariableArg(ARG2).length());
			_file.WriteString(GetVariableArg(ARG2));
		}
		if(state[TEMPLATE][TARGET])
		{
			_file.Write(GetTemplateArg(TARGET).length());
			_file.WriteString(GetTemplateArg(TARGET));
		}
		else if(state[VARIABLE][TARGET])
		{
			_file.Write(GetVariableArg(TARGET).length());
			_file.WriteString(GetVariableArg(TARGET));
		} 
		return true;
	}
	return false;
}


AbstractAction* Vector2ToSphericalAction::_LoadFromFile(File& _file)
{
	Vector2ToSphericalAction* action = new Vector2ToSphericalAction(Variable<Vector2>::VECTOR_2_TO_SPHERICAL_MESSAGE);
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
	if(action->state[TEMPLATE][ARG2])
	{
		StringANSI templateArg;
		_file.Read(length);
		_file.ReadString(templateArg, length);
		action->SetTemplateArg(ARG2, templateArg); 
	}
	else if(action->state[VARIABLE][ARG2])
	{
		StringANSI variableArg;
		_file.Read(length);
		_file.ReadString(variableArg, length);
		action->SetVariableArg(ARG2, variableArg);
	}
	if(action->state[TEMPLATE][TARGET])
	{
		StringANSI templateArg;
		_file.Read(length);
		_file.ReadString(templateArg, length);
		action->SetTemplateArg(TARGET, templateArg); 
	}
	else if(action->state[VARIABLE][TARGET])
	{
		StringANSI variableArg;
		_file.Read(length);
		_file.ReadString(variableArg, length);
		action->SetVariableArg(TARGET, variableArg);
	}
	return action;
}