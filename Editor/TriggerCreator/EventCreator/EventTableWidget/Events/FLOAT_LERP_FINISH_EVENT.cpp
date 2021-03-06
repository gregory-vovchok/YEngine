#include "../EventTableWidget.h"
#include <Editor/TriggerCreator/TriggerCreator.h>
#include <Engine/Core/Trigger/Event/Events.h>



void EventTableWidget::FLOAT_LERP_FINISH_GetEditorTypeForCell(const QModelIndex& _index, const QString& _eventType, int& _editor)
{
	if(_eventType == "FLOAT_LERP_FINISH")
	{
		if(_index.column() == VALUE)
		{
			switch(_index.row())
			{
				case SOURCE_PROPERTY:
				{
					if(item(SOURCE_PROPERTY, ARG_MODE)->text() == "VARIABLE")
					{
						_editor = UniversalDelegate::FLOAT_LERP_EDITOR;
						return;
					}
					else if(item(SOURCE_PROPERTY, ARG_MODE)->text() == "TEMPLATE")
					{
						_editor = UniversalDelegate::STRING_EXPR_EDITOR;
						return;
					}
					break;
				}

				case DEACTIVATION_MODE_PROPERTY:
				{
					_editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}
			}
		}
		else if(_index.column() == ARG_MODE)
		{
			switch(_index.row())
			{
				case SOURCE_PROPERTY:
				{
					_editor = UniversalDelegate::COMBO_BOX_EDITOR;
					return;
				}
			}
		}
		_editor = UniversalDelegate::NO_EDIT;
	}
}



bool EventTableWidget::FLOAT_LERP_FINISH_UpdateRow(const QModelIndex& _index, const QString& _type)
{
	if(_type == "FLOAT_LERP_FINISH") 
	{
		if(_index.row() == TYPE_PROPERTY && _index.column() == VALUE)
		{
			SetDefaultState();
			SetPropertyEnable(ARG1_PROPERTY, false);
			SetPropertyEnable(ARG2_PROPERTY, false);
			SetPropertyEnable(ARG3_PROPERTY, false);
			SetPropertyEnable(ARG4_PROPERTY, false);
			SetPropertyEnable(ARG5_PROPERTY, false);
			delegate->SetComboValuesForCell(indexFromItem(item(SOURCE_PROPERTY, ARG_MODE)), argMode_VARIABLE_TEMPLATE_ComboList);
			SetCellText(SOURCE_PROPERTY, ARG_MODE, argMode_VARIABLE_TEMPLATE_ComboList.at(0));
			delegate->SetComboValuesForCell(indexFromItem(item(DEACTIVATION_MODE_PROPERTY, VALUE)), deactivationMode_EVER_AUTO_ComboList);
			if(item(DEACTIVATION_MODE_PROPERTY, VALUE)->text().isEmpty()) { SetCellText(DEACTIVATION_MODE_PROPERTY, VALUE, deactivationMode_EVER_AUTO_ComboList.at(0)); }
		}
		if(_index.row() == SOURCE_PROPERTY && _index.column() == ARG_MODE)
		{
			SetDefaultProperty(SOURCE_PROPERTY);
			SetCellText(SOURCE_PROPERTY, CONTENT, "Name"); 
			SetCellText(SOURCE_PROPERTY, DATA_TYPE, "Float lerp"); 
		}
		return true;
	}  
	return false;
}



QString EventTableWidget::FLOAT_LERP_FINISH_CreateAutoName(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "FLOAT_LERP_FINISH")
	{ 
		QString name;

		if(item(SOURCE_PROPERTY, ARG_MODE)->text() == "VARIABLE")
		{
			name += "_" + item(SOURCE_PROPERTY, VALUE)->text(); 
		}
		return name;
	}
	return "";
}



bool EventTableWidget::FLOAT_LERP_FINISH_UpdateSourceVariablePropertyStatus(void)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "FLOAT_LERP_FINISH")
	{ 
		UpdateFloatLerp(SOURCE_PROPERTY);
		return true;
	}
	return false;
}



void EventTableWidget::FLOAT_LERP_FINISH_DropEvent(QTableWidgetItem* _it, const QModelIndex& _index, const QString& _suffix, QString& _fileName)
{
	if(item(TYPE_PROPERTY, VALUE)->text() == "FLOAT_LERP_FINISH")
	{
		if(item(_index.row(), ARG_MODE)->text() == "VARIABLE")
		{
			if(_index.row() == SOURCE_PROPERTY)
			{
				FloatLerpDropEvent(_it, _index, _suffix, _fileName);
			}
		}
		else if(item(_index.row(), ARG_MODE) ->text() == "TEMPLATE")
		{ 
			StringExprDropEvent(_it, _index, _suffix, _fileName);
		}
	}
}


void EventCreator::FLOAT_LERP_FINISH_SetEvent(int _eventType)
{
	if(_eventType == FloatLerp::FLOAT_LERP_FINISH_MESSAGE)
	{
		eventTable->SetCellText(EventTableWidget::TYPE_PROPERTY, EventTableWidget::VALUE, "FLOAT_LERP_FINISH");

		FloatLerpFinishEvent* derived = dynamic_cast<FloatLerpFinishEvent*>(event);
		
		if(derived)
		{
			if(derived->GetArgState(AbstractEvent::VARIABLE, AbstractEvent::SOURCE))
			{
				eventTable->SetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::ARG_MODE, "VARIABLE");
				eventTable->SetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::VALUE, derived->GetVariableArg(AbstractEvent::SOURCE).c_str());
			}
			else if(derived->GetArgState(AbstractEvent::TEMPLATE, AbstractEvent::SOURCE))
			{
				eventTable->SetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::ARG_MODE, "TEMPLATE");
				eventTable->SetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::VALUE, derived->GetTemplateArg(AbstractEvent::SOURCE).c_str());
			}
		}
	}
}


void EventCreator::FLOAT_LERP_FINISH_Create(void)
{
	if(eventTable->GetCellText(EventTableWidget::TYPE_PROPERTY, EventTableWidget::VALUE) == "FLOAT_LERP_FINISH")
	{
		event = Trigger::_CreateEvent(FloatLerp::FLOAT_LERP_FINISH_MESSAGE);

		if(event)
		{
			if(eventTable->GetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::ARG_MODE) == "VARIABLE")
			{
				event->SetVariableArg(AbstractEvent::SOURCE, eventTable->GetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::VALUE).toStdString());
				if(event->GetArgState(AbstractEvent::ASSET_TYPE, AbstractEvent::SOURCE) == AssetLibrary::UNKNOWN_ASSET)
				{
					int32 assetType = AssetLibrary::_IsAssetExist(eventTable->GetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::VALUE).toStdString());

					event->SetArgAssetType(AbstractEvent::SOURCE, assetType);
				}
			}
			else if(eventTable->GetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::ARG_MODE) == "TEMPLATE")
			{
				event->SetTemplateArg(AbstractEvent::SOURCE, eventTable->GetCellText(EventTableWidget::SOURCE_PROPERTY, EventTableWidget::VALUE).toStdString());
			}
		}
	} 
}
