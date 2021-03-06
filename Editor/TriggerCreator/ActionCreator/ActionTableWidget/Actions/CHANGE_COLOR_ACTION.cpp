#include "../ActionTableWidget.h"
#include <Editor/TriggerCreator/TriggerCreator.h>
#include <Engine/Core/Trigger/Action/Actions.h>


void ActionTableWidget::CHANGE_COLOR_GetEditorTypeForCell(const QModelIndex& _index, const QString& _actionType, int& _editor)
{
	if(_actionType == "CHANGE_COLOR")
	{
		if(_index.column() == VALUE)
		{
			switch(_index.row())
			{
				case ARG1_PROPERTY:
				{
				    _editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}

				case ARG2_PROPERTY:
				{
					if(item(ARG1_PROPERTY, VALUE)->text() == "RGB_COLOR")
					{
						if(item(ARG2_PROPERTY, ARG_MODE)->text() == "KEY")
						{
							_editor = UniversalDelegate::VECTOR_3_RGB_EDITOR;
							return;
						}
						else if(item(ARG2_PROPERTY, ARG_MODE)->text() == "VARIABLE")
						{
							_editor = UniversalDelegate::COLORABLE_OBJECT_EDITOR;
							return;
						}
						else if(item(ARG2_PROPERTY, ARG_MODE)->text() == "TEMPLATE")
						{
							_editor = UniversalDelegate::STRING_EXPR_EDITOR;
							return;
						}
					}
					else if(item(ARG1_PROPERTY, VALUE)->text() == "HSL_COLOR")
					{
						if(item(ARG2_PROPERTY, ARG_MODE)->text() == "KEY")
						{
							_editor = UniversalDelegate::VECTOR_3_HSL_EDITOR;
							return;
						}
						else if(item(ARG2_PROPERTY, ARG_MODE)->text() == "VARIABLE")
						{
							_editor = UniversalDelegate::COLORABLE_OBJECT_EDITOR;
							return;
						}
						else if(item(ARG2_PROPERTY, ARG_MODE)->text() == "TEMPLATE")
						{
							_editor = UniversalDelegate::STRING_EXPR_EDITOR;
							return;
						}
					}
					break;
				}
				
				case TARGET_PROPERTY:
				{
					if(item(TARGET_PROPERTY, ARG_MODE)->text() == "VARIABLE")
					{
						_editor = UniversalDelegate::COLORABLE_OBJECT_EDITOR;
						return;
					}
					else if(item(TARGET_PROPERTY, ARG_MODE)->text() == "TEMPLATE")
					{
						_editor = UniversalDelegate::STRING_EXPR_EDITOR;
						return;
					}
					break;
				}
			}
		}
		else if(_index.column() == ARG_MODE)
		{
			switch(_index.row())
			{
				case ARG1_PROPERTY:
				{
					_editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}

				case ARG2_PROPERTY:
				{
					_editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}

				case TARGET_PROPERTY:
				{
					_editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}
			}
		}
		_editor = UniversalDelegate::NO_EDIT;
	}
}




bool ActionTableWidget::CHANGE_COLOR_UpdateRow(const QModelIndex& _index, const QString& _type)
{
	if(_type == "CHANGE_COLOR") 
	{
		if(_index.row() == TYPE_PROPERTY && _index.column() == VALUE)
		{
			SetDefaultState();
			SetPropertyEnable(ARG3_PROPERTY, false);
			SetPropertyEnable(ARG4_PROPERTY, false);
			SetPropertyEnable(ARG5_PROPERTY, false);
			delegate->SetComboValuesForCell(indexFromItem(item(ARG1_PROPERTY, VALUE)), colorTypeArgsComboList);

			SetCellText(ARG1_PROPERTY, CONTENT, "Arg type");
			delegate->SetComboValuesForCell(indexFromItem(item(ARG2_PROPERTY, ARG_MODE)), argMode_KEY_VARIABLE_TEMPLATE_ComboList);
			SetCellText(ARG2_PROPERTY, ARG_MODE, argMode_KEY_VARIABLE_TEMPLATE_ComboList.at(0));
			delegate->SetComboValuesForCell(indexFromItem(item(TARGET_PROPERTY, ARG_MODE)), argMode_VARIABLE_TEMPLATE_ComboList);
			SetCellText(TARGET_PROPERTY, ARG_MODE, argMode_VARIABLE_TEMPLATE_ComboList.at(0));
		}
		else if((_index.row() == ARG1_PROPERTY && _index.column() == VALUE) ||
			    (_index.row() == ARG2_PROPERTY && _index.column() == ARG_MODE))
		{
			SetDefaultProperty(ARG2_PROPERTY);

			if(item(ARG1_PROPERTY, VALUE)->text() == "RGB_COLOR")
			{
				if(item(ARG2_PROPERTY, ARG_MODE)->text() == "KEY")
				{
					SetCellText(ARG2_PROPERTY, CONTENT, "Color"); 
					SetCellText(ARG2_PROPERTY, DATA_TYPE, "Vector3"); 
				}
				else
				{
					SetCellText(ARG2_PROPERTY, CONTENT, "Color"); 
					SetCellText(ARG2_PROPERTY, DATA_TYPE, "Colorable object"); 
				}
			}
			else if(item(ARG1_PROPERTY, VALUE)->text() == "HSL_COLOR")
			{
				if(item(ARG2_PROPERTY, ARG_MODE)->text() == "KEY")
				{
					SetCellText(ARG2_PROPERTY, CONTENT, "Color"); 
					SetCellText(ARG2_PROPERTY, DATA_TYPE, "Vector3"); 
				}
				else
				{
					SetCellText(ARG2_PROPERTY, CONTENT, "Color"); 
					SetCellText(ARG2_PROPERTY, DATA_TYPE, "Colorable object"); 
				}
			}
		}
		else if(_index.row() == TARGET_PROPERTY && _index.column() == ARG_MODE)
		{
			SetDefaultProperty(TARGET_PROPERTY);
			SetCellText(TARGET_PROPERTY, CONTENT, "Name"); 
			SetCellText(TARGET_PROPERTY, DATA_TYPE, "Colorable object"); 
		}
		return true;
	}  
	return false;
}



QString ActionTableWidget::CHANGE_COLOR_CreateAutoName(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "CHANGE_COLOR")
	{ 
		QString name;

		if(item(TARGET_PROPERTY, ARG_MODE)->text() == "VARIABLE")
		{
			name += "_" + item(TARGET_PROPERTY, VALUE)->text(); 
		}
		if(item(ARG2_PROPERTY, ARG_MODE)->text() == "VARIABLE")
		{
			name += "_" + item(ARG2_PROPERTY, VALUE)->text();
		}
		return name;
	}
	return "";
}


bool ActionTableWidget::CHANGE_COLOR_UpdateTargetVariablePropertyStatus(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "CHANGE_COLOR")
	{ 
		UpdateColorableObject(TARGET_PROPERTY);
		return true;
	}
	return false;
}



bool ActionTableWidget::CHANGE_COLOR_UpdateArg1PropertyStatus(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "CHANGE_COLOR")
	{ 
		SetPropertyValid(ARG1_PROPERTY, true);
		return true;
	}
	return false;
}


bool ActionTableWidget::CHANGE_COLOR_UpdateArg2VariablePropertyStatus(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "CHANGE_COLOR")
	{
		if(item(ARG1_PROPERTY, VALUE)->text() == "RGB_COLOR")
		{
			UpdateColorableObject(ARG2_PROPERTY);
		}
		else if(item(ARG1_PROPERTY, VALUE)->text() == "HSL_COLOR")
		{
			UpdateColorableObject(ARG2_PROPERTY);
		}
		return true;
	}
	return false;
}


void ActionTableWidget::CHANGE_COLOR_DropEvent(QTableWidgetItem* _it, const QModelIndex& _index, const QString& _suffix, QString& _fileName)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "CHANGE_COLOR")
	{
		if(item(_index.row(), ARG_MODE)->text() == "VARIABLE")
		{
			if(_index.row() == ARG2_PROPERTY)
			{ 
				if(item(ARG1_PROPERTY, VALUE)->text() == "RGB_COLOR")
				{
					ColorableObjectDropEvent(_it, _index, _suffix, _fileName);
				}
				else if(item(ARG1_PROPERTY, VALUE)->text() == "HSL_COLOR")
				{
					ColorableObjectDropEvent(_it, _index, _suffix, _fileName);
				}
			}
			else if(_index.row() == TARGET_PROPERTY)
			{
				ColorableObjectDropEvent(_it, _index, _suffix, _fileName);  
			}
		}
		else if(item(_index.row(), ARG_MODE) ->text() == "TEMPLATE")
		{ 
			StringExprDropEvent(_it, _index, _suffix, _fileName);
		}
	}
}


void ActionCreator::CHANGE_COLOR_SetAction(int _actionType)
{
	if(_actionType == ColorableObject::CHANGE_COLOR_HSL_MESSAGE)
	{
		actionTable->SetCellText(ActionTableWidget::TYPE_PROPERTY, ActionTableWidget::VALUE, "CHANGE_COLOR");

		ChangeColorHSLAction* derived = dynamic_cast<ChangeColorHSLAction*>(action);
		
		if(derived)
		{
			actionTable->SetCellText(ActionTableWidget::ARG1_PROPERTY, ActionTableWidget::VALUE, "HSL_COLOR");
			if(derived->GetArgState(AbstractAction::KEY, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "KEY");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, Vector3ToString(derived->GetVector3KeyArg(AbstractAction::ARG1)));
			}
			else if(derived->GetArgState(AbstractAction::VARIABLE, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "VARIABLE");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, derived->GetVariableArg(AbstractAction::ARG1).c_str());
			}
			else if(derived->GetArgState(AbstractAction::TEMPLATE, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "TEMPLATE");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, derived->GetTemplateArg(AbstractAction::ARG1).c_str());
			}
			if(derived->GetArgState(AbstractAction::VARIABLE, AbstractAction::TARGET))
			{
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE, "VARIABLE");
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE, derived->GetVariableArg(AbstractAction::TARGET).c_str());
			}
			else if(derived->GetArgState(AbstractAction::TEMPLATE, AbstractAction::TARGET))
			{
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE, "TEMPLATE");
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE, derived->GetTemplateArg(AbstractAction::TARGET).c_str());
			}
		}
	}
	else if(_actionType == ColorableObject::CHANGE_COLOR_RGB_MESSAGE)
	{
		actionTable->SetCellText(ActionTableWidget::TYPE_PROPERTY, ActionTableWidget::VALUE, "CHANGE_COLOR");

		ChangeColorRGBAction* derived = dynamic_cast<ChangeColorRGBAction*>(action);
		
		if(derived)
		{
			actionTable->SetCellText(ActionTableWidget::ARG1_PROPERTY, ActionTableWidget::VALUE, "RGB_COLOR");
			if(derived->GetArgState(AbstractAction::KEY, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "KEY");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, Vector3ToString(derived->GetVector3KeyArg(AbstractAction::ARG1)));
			}
			else if(derived->GetArgState(AbstractAction::VARIABLE, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "VARIABLE");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, derived->GetVariableArg(AbstractAction::ARG1).c_str());
			}
			else if(derived->GetArgState(AbstractAction::TEMPLATE, AbstractAction::ARG1))
			{
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE, "TEMPLATE");
				actionTable->SetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE, derived->GetTemplateArg(AbstractAction::ARG1).c_str());
			}
			if(derived->GetArgState(AbstractAction::VARIABLE, AbstractAction::TARGET))
			{
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE, "VARIABLE");
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE, derived->GetVariableArg(AbstractAction::TARGET).c_str());
			}
			else if(derived->GetArgState(AbstractAction::TEMPLATE, AbstractAction::TARGET))
			{
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE, "TEMPLATE");
				actionTable->SetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE, derived->GetTemplateArg(AbstractAction::TARGET).c_str());
			}
		}
	}
}


void ActionCreator::CHANGE_COLOR_Create(void)
{
	if(actionTable->GetCellText(ActionTableWidget::TYPE_PROPERTY, ActionTableWidget::VALUE) == "CHANGE_COLOR")
	{
		if(actionTable->GetCellText(ActionTableWidget::ARG1_PROPERTY, ActionTableWidget::VALUE) == "HSL_COLOR")
		{
			action = Trigger::_CreateAction(ColorableObject::CHANGE_COLOR_HSL_MESSAGE);

			if(action)
			{
				if(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE) == "VARIABLE")
				{
					action->SetVariableArg(AbstractAction::TARGET, actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());
					if(action->GetArgState(AbstractAction::ASSET_TYPE, AbstractAction::TARGET) == AssetLibrary::UNKNOWN_ASSET)
					{
						int32 assetType = AssetLibrary::_IsAssetExist(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());

						action->SetArgAssetType(AbstractAction::TARGET, assetType);
					}
				}
				else if(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE) == "TEMPLATE")
				{
					action->SetTemplateArg(AbstractAction::TARGET, actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());
				}
				if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "KEY")
				{
					action->SetVector3KeyArg(AbstractAction::ARG1, StringToVector3(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE)));
				}
				else if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "VARIABLE")
				{
					action->SetVariableArg(AbstractAction::ARG1, actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());
					if(action->GetArgState(AbstractAction::ASSET_TYPE, AbstractAction::ARG1) == AssetLibrary::UNKNOWN_ASSET)
					{
						int32 assetType = AssetLibrary::_IsAssetExist(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());

						action->SetArgAssetType(AbstractAction::ARG1, assetType);
					}
				}
				else if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "TEMPLATE")
				{
					action->SetTemplateArg(AbstractAction::ARG1, actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());
				}
			}
		}
		else if(actionTable->GetCellText(ActionTableWidget::ARG1_PROPERTY, ActionTableWidget::VALUE) == "RGB_COLOR")
		{  
			action = Trigger::_CreateAction(ColorableObject::CHANGE_COLOR_RGB_MESSAGE);

			if(action)
			{
				if(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE) == "VARIABLE")
				{
					action->SetVariableArg(AbstractAction::TARGET, actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());
					if(action->GetArgState(AbstractAction::ASSET_TYPE, AbstractAction::TARGET) == AssetLibrary::UNKNOWN_ASSET)
					{
						int32 assetType = AssetLibrary::_IsAssetExist(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());

						action->SetArgAssetType(AbstractAction::TARGET, assetType);
					}
				}
				else if(actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::ARG_MODE) == "TEMPLATE")
				{
					action->SetTemplateArg(AbstractAction::TARGET, actionTable->GetCellText(ActionTableWidget::TARGET_PROPERTY, ActionTableWidget::VALUE).toStdString());
				}
				if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "KEY")
				{
					action->SetVector3KeyArg(AbstractAction::ARG1, StringToVector3(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE)));
				}
				else if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "VARIABLE")
				{
					action->SetVariableArg(AbstractAction::ARG1, actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());
					if(action->GetArgState(AbstractAction::ASSET_TYPE, AbstractAction::ARG1) == AssetLibrary::UNKNOWN_ASSET)
					{
						int32 assetType = AssetLibrary::_IsAssetExist(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());

						action->SetArgAssetType(AbstractAction::ARG1, assetType);
					}
				}
				else if(actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::ARG_MODE) == "TEMPLATE")
				{
					action->SetTemplateArg(AbstractAction::ARG1, actionTable->GetCellText(ActionTableWidget::ARG2_PROPERTY, ActionTableWidget::VALUE).toStdString());
				}
			}
		}
	} 
}
