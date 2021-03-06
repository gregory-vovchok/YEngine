#ifndef TEXTURECREATOR_H
#define TEXTURECREATOR_H
#include <QtGui/QWidget>
#include <QDialog>
#include <Editor/AnimatedLabel/AnimatedLabel.h>
#include <Engine/Output/Graphics/Texture/Texture2D/Texture2D.h>
#include <Editor/Viewport/Viewport.h>
#include <Editor/TextureCreator/TextureViewer/TextureViewer.h>
#include <Editor/TextureCreator/TextureShapeListWidget/TextureShapeListWidget.h>
#include <Editor/SpaceUnitsDialog/SpaceUnitsDialog.h>
#include <Editor/FloatSpinBox/FloatSpinBox.h>
#include <Editor/IntSpinBox/IntSpinBox.h>
class TextureCreator: public QDialog
{
	Q_OBJECT
	public: enum
	{
		TEXTURE_EDITOR,
		TEXTURED_ANIMATION_EDITOR
	};
	private: Viewport* viewport;
    private: TextureViewer* engine;
	private: QTimer intervalTimer;
	
	private: Texture2D* texture;
	private: TexturedAnimation* texturedAnimation;
	private: Atlas2D* atlas;
    private: QLabel *nameLabel; 
    private: QLineEdit *nameLineEdit;
	private: int nameMaxLength;
	private: QPushButton* loadTextureButton;
	private: static QString startDir;


	private: QTabWidget *tabWidget;
	private: QWidget *propertiesTab;
  	private: QScrollArea* texturePropertyScrollArea;
	private: QWidget* texturePropertyScrollAreaWidget;
  	private: QScrollArea* texturedAnimationPropertyScrollArea;
	private: QWidget* texturedAnimationPropertyScrollAreaWidget;
	private: QLabel* textureWidthLabel;
	private: IntSpinBox* textureWidthSpinBox;
	private: QLabel* textureHeightLabel;
    private: IntSpinBox* textureHeightSpinBox;

	private: int sizeMin, sizeMax;
	private: QLabel * textureFilteringLabel;
	private: QComboBox *textureFilteringComboBox;
	private: QGroupBox *animationGroupBox;
	private: float animationMinDuration, animationMaxDuration; 
	private: float animationMinFPS, animationMaxFPS;
	private: float animationMinFrameDuration, animationMaxFrameDuration;
    private: QLabel* animationFPSLabel;
	private: FloatSpinBox* animationFPSSpinBox;
    private: QLabel* animationDurationLabel;
	private: FloatSpinBox* animationDurationSpinBox;
    private: QLabel* animationFrameDurationLabel;
    private: FloatSpinBox* animationFrameDurationSpinBox;
	private: QLabel* animationElapsedTimeLabel;
	private: FloatSpinBox* animationElapsedTimeSpinBox;
	private: QGroupBox* animationPlayingModeGroupBox;
    private: QRadioButton* animationForwardRadioButton;
    private: QRadioButton* animationBackwardRadioButton;
    private: QRadioButton* animationPingPongRadioButton;
    private: QRadioButton* animationOnewayRadioButton;
    private: QRadioButton* animationLoopRadioButton;
    private: QRadioButton* animationSingleShotRadioButton;
    private: QFrame *animationCurrentFrameLine;

    private: QPushButton* animationStopButton;
    private: QPushButton* animationPlayButton;
    private: QLabel* animationCurrentFrameLabel;
    private: QSpinBox* animationCurrentFrameSpinBox;
	private: QGroupBox* atlasGroupBox;
    private: QLabel* atlasNameLabel;
	private: QLineEdit* atlasNameLineEdit;

    private: QPushButton* animationImportAtlasButton;
	private: QPushButton* animationSaveAtlasAsButton;
	private: QPushButton* animationCreateAtlasButton;
    private: QLabel* atlasAmountOfAnimFrameLabel;
	private: QGroupBox* atlasFrameGroupBox;
    private: QLabel* atlasFrameNameLabel;
	private: QLineEdit* atlasFrameNameLineEdit;
    private: QLabel* atlasFrameWidthLabel;
	private: QSpinBox* atlasFrameWidthSpinBox;
	private: QLabel* atlasFrameHeightLabel;
    private: QSpinBox* atlasFrameHeightSpinBox;
	private: QLabel * atlasFilteringLabel;
	private: QComboBox *atlasFilteringComboBox;
    private: QLabel* atlasPositionOffsetLabel;
	private: FloatSpinBox* atlasXPositionOffsetSpinBox;
	private: FloatSpinBox* atlasYPositionOffsetSpinBox;
	private: FloatSpinBox* atlasZPositionOffsetSpinBox;
    private: QFrame *texturedAnimationPositionOffsetLine;
	private: QLabel* animationShowPreviousFrameLabel;
    private: QCheckBox* animationShowPreviousFrameCheckBox;
	private: QGroupBox* texturedAnimationGroupBox;
	private: QLabel* texturedAnimationPositionOffsetEnableLabel;
    private: QCheckBox* texturedAnimationPositionOffsetEnableCheckBox;

	private: QPushButton* texturedAnimationPositionOffsetTemplateButton;
	private: QWidget *hitboxTab;
    private: QLabel* hitboxNameLabel; 
    private: QLineEdit *hitboxNameLineEdit;

	private: SimpleList<QString> hitboxNames;
	private: QLabel *brushLabel;
	private: QComboBox *brushComboBox;
	private: QLabel *circleSegmentsLabel;
	private: IntSpinBox* circleSegmentsSpinBox;
	private: QLabel *buildModeLabel;
    private: QComboBox *buildModeComboBox;
	private: QLabel *hitboxEnableLabel;
	private: QCheckBox *hitboxEnableCheckBox;
	private: QLabel *lockLabel; 
	private: QCheckBox *lockCheckBox;
	private: TextureShapeListWidget *shapeList;
	private: int shapeNumber;
	private: QFileDialog* saveShapeDialog;
	private: QFileDialog* importShapeDialog;

	private: QToolButton *addShapeToolButton;
	private: QToolButton *removeShapeToolButton;
	private: QToolButton *createSubpointsToolButton;
    private: QPushButton *importHitboxPushButton;
	private: QPushButton *changePivotPushButton;
	private: QPushButton *hitboxSaveAsPushButton;
	private: QWidget *vectorLerpTab;
    private: QLabel *vectorLerpNameLabel; 
    private: QLineEdit *vectorLerpNameLineEdit;

	private: QPushButton *vectorLerpImportPushButton;
	private: QPushButton *vectorLerpSaveAsPushButton;
	private: QLabel *vectorLerpModeLabel;
	private: QComboBox *vectorLerpModeComboBox;
	private: QLabel *vectorLerpSegmentsLabel;
	private: IntSpinBox* vectorLerpSegmentsSpinBox;
	private: QPushButton* vectorLerpSaveCurvePushButton;
    private: QFileDialog* saveCurveDialog;
	private: QLabel* vectorLerpCurrentLabel;
	private: FloatSpinBox* vectorLerpCurrentXSpinBox;
	private: FloatSpinBox* vectorLerpCurrentYSpinBox;
	private: FloatSpinBox* vectorLerpCurrentZSpinBox;
	private: QLabel* vectorLerpDeltaLabel;
	private: FloatSpinBox* vectorLerpDeltaXSpinBox;
	private: FloatSpinBox* vectorLerpDeltaYSpinBox;
	private: FloatSpinBox* vectorLerpDeltaZSpinBox;
	private: QLabel* vectorLerpFloatLerpLabel;
	private: QScrollArea* vectorLerpFloatLerpScrollArea;
	private: QWidget* vectorLerpFloatLerpScrollAreaWidget;
	private: QLabel *vectorLerpFloatLerpNameLabel;
    private: QLineEdit* vectorLerpFloatLerpNameLineEdit;

	private: QPushButton* vectorLerpFloatLerpImportPushButton;
	private: QPushButton* vectorLerpFloatLerpSaveAsPushButton;
	private: QLabel *vectorLerpFloatLerpTargetLabel;
	private: FloatSpinBox* vectorLerpFloatLerpTargetSpinBox;
	private: QLabel *vectorLerpFloatLerpCurrentLabel;
	private: FloatSpinBox* vectorLerpFloatLerpCurrentSpinBox;
    private: QLabel *vectorLerpFloatLerpTLabel;
	private: FloatSpinBox* vectorLerpFloatLerpTSpinBox;
    private: QLabel *vectorLerpFloatLerpDeltaLabel;
	private: FloatSpinBox* vectorLerpFloatLerpDeltaSpinBox;
	private: QLabel *vectorLerpFloatLerpModeLabel;
	private: QComboBox* vectorLerpFloatLerpModeComboBox;
	private: QLabel* vectorLerpFloatLerpPlayingSpeedLabel;
	private: FloatSpinBox* vectorLerpFloatLerpPlayingSpeedSpinBox;
	private: QLabel* vectorLerpFloatLerpPlayingDurationLabel;
	private: FloatSpinBox* vectorLerpFloatLerpPlayingDurationSpinBox;
	private: QLabel* vectorLerpFloatLerpElapsedTimeLabel;
	private: FloatSpinBox* vectorLerpFloatLerpElapsedTimeSpinBox;
	private: QGroupBox* vectorLerpFloatLerpPlayingModeGroupBox;
	private: QRadioButton* vectorLerpFloatLerpForwardRadioButton;
	private: QRadioButton* vectorLerpFloatLerpBackwardRadioButton;
	private: QRadioButton* vectorLerpFloatLerpPingPongRadioButton;
	private: QRadioButton* vectorLerpFloatLerpOnewayRadioButton;
	private: QRadioButton* vectorLerpFloatLerpSingleShotRadioButton;
    private: QRadioButton* vectorLerpFloatLerpLoopRadioButton;

	private: QPushButton* vectorLerpFloatLerpStopPushButton;
	private: QPushButton* vectorLerpFloatLerpPlayPushButton;
	private: QWidget *tileboxTab;
	private: QLabel* currentZoomScaleLabel;

	private: QLabel* worldCursorPositionLabel;
	private: QLabel* amountOfPointsLabel;
	private: QMenuBar* menuBar;
    private: QMenu* pointsMenu;
	private: QAction* verticesSizeAct;
	private: QAction* verticesShowAct;
	private: bool verticesShowEnable;
	private: QAction* verticesImportAct;
	private: QAction* verticesSaveAsAct;
	private: QAction* pointsAntiAliasingAct;
    private: QMenu* linesMenu;
	private: QAction* edgesWidthAct;
	private: QAction* edgesShowAct;
	private: bool edgesShowEnable;
	private: QMenu* linesAntiAliasingMenu;
	private: QAction* linesAntiAliasingAct;
	private: QMenu* viewMenu;
    private: QMenu* decorationsMenu;
	private: QAction* importDecorationAct;
	private: QAction* clearDecorationsAct;
	private: QAction* saveDecorationsAsAct;
	private: QMenu* backgroundMenu;
	private: QAction* backgroundColorAct;
	private: RGBA backgroundColor;
	private: QMenu* cameraMenu;
	private: QAction* cameraSaveAsAct;
	private: QMenu* spriteMenu;
	private: QAction* spriteSaveAsAct;
	private: QMenu* quadMenu;
	private: QAction* quadShowAct;
	private: bool quadShowEnable;
	private: QAction* quadImportAct;
	private: QAction* quadSaveAsAct;
	private: QMenu* gizmoMenu;
	private: QAction* gizmoShowAct;
	private: bool gizmoXYShowEnable;
	private: QMenu* gridMenu;
	private: QAction* gridShowAct;
	private: bool gridShowEnable;
	private: QAction* spaceUnitsAct;
	private: bool vectorLerpShowCurveEnable;
	private: QMenu* vectorLerpMenu;
	private: QAction* vectorLerpShowCurveAct;

	private: QToolButton* homeButton;

	private: bool fastCreatingEnable;

	private: int32 editorMode;
	private: QToolButton* helpButton;
    private: QPushButton* cancelButton;
    private: QPushButton* okButton;
    public: TextureCreator(QWidget* _parent = NIL);
    public: virtual ~TextureCreator(void);
	private slots: void ShowDoc(void);
    private slots: void TextureIsOk(void);
	public: int GetEditorMode(void)const;
    private slots: void TexturedAnimationIsOk(void);
	public: Texture2D* GetTexture(void);
	public: TexturedAnimation* GetTexturedAnimation(void);
	public: void SaveTexture(void);
	private slots: void CurrentTabIsChanged(int _index);
    protected: virtual void closeEvent(QCloseEvent *_event);
    public: void SetVectorLerpEditor(void);
    public: void SetFloatLerpEditor(void);
    public: void SetHitboxEditor(void);
    public: void SetTextureEditor(void);
    public: void SetTexturedAnimationEditor(void);
	private: void CreateEngine(void);
	private: void CreateViewport(void);
	private slots: void CallFrame(void);
	public: void EnginePause(void);
	public: void EnginePlay(void);
	public: void SetZoomValue(int _zoom);
	public: float GetZoom100(void)const;
	public slots: void SetHome(void);
	public slots: void SetCameraHome(void);
	public: void UpdateCursorPosition(Vector2 _point);
	private: void CreateMenu(void);
	private: void CreatePointsMenu(void);
	private: void CreatePointsShowAct(void);
	private: void CreatePointsSizeAct(void);
	public slots: void ChangePointsSize(void);
	private slots: void ChangePointsShow(void);
	private: void CreatePointsImportAct(void);
	private: void CreateSavePointsAsAct(void);
	private: void CreatePointsAntiAliasingAct(void);
	private slots: void ChangePointsAntiAliasing(void);
	public: bool GetPointsAntiAliasingFromFile(void);
	private: void CreateLinesMenu(void);
	private: void CreateLinesWidthAct(void);
	public slots: void ChangeLinesWidth(void);
	private: void CreateLinesShowAct(void);
	private slots: void ChangeLinesShow(void);
	private: void CreateLinesAntiAliasingAct(void);
	private slots: void ChangeLinesAntiAliasing(void);
	public: bool GetLinesAntiAliasingFromFile(void);
	private: void CreateSpriteMenu(void);
	private: void CreateSaveSpriteAsAct(void);
	private slots: void SaveSpriteAs(void);
	private: void CreateQuadMenu(void);
	private: void CreateQuadShowAct(void);
	private slots: void ChangeQuadShow(void);
	private: void CreateSaveQuadAsAct(void);
	public slots: void SaveQuadAs(void);
	private: void CreateQuadImportAct(void);
	public slots: void QuadImport(void);
	private: void CreateGizmoMenu(void);
	private: void CreateGizmoShowAct(void);
	private slots: void ChangeGizmoShow(void);
	private: void CreateViewMenu(void);
	private: void CreateCameraMenu(void);
	private: void CreateSaveCameraAsAct(void);
	private slots: void SaveCameraAs(void);
	private: void CreateDecorationsMenu(void);
	private: void CreateImportDecorationAct(void);
	private slots: void ImportDecoration(void);
	private: void CreateClearDecorationsAct(void);
	private: void CreateSaveDecorationsAsAct(void);
	private slots: void ClearDecorations(void);
	private slots: void SaveDecorationsAs(void);
	private: void CreateBackgroundMenu(void);
	private: void CreateBackgroundColorAct(void);
	private: void CreateGridMenu(void);
	private: void CreateGridShowAct(void);
	private slots: void ChangeGridShow(void);
	private: void CreateSpaceUnitsAct(void);
	public slots: void ChangeSpaceUnits(void);
	public slots: void ChangeBackgroundColor(void);
	private: void CreateVectorLerpMenu(void);
	private: void CreateVectorLerpShowCurveAct(void);
	private slots: void ChangeVectorLerpShowCurve(void);
	public: QString GetObjectName(void)const;
	public: void SetNameDisable(bool _disable);
	public: void SetObjectName(QString _name);
	private slots: void NameIsChanged(void);
	public: void SetVectorLerpNameDisable(bool _disable);
	public: void SetFloatLerpNameDisable(bool _disable);
	public: void SetVectorLerpObjectName(QString _name);
	public: void SetFloatLerpObjectName(QString _name);
	public: void SetHitboxNameDisable(bool _disable);
	public: void SetHitboxObjectName(QString _name);
	public: void SetAtlasObjectName(QString _name);
	private slots: void HitboxNameIsChanged(QString _name);
	public: void SetAtlas(QString _name);
	public: int GetAnimationCurrentFrame(void)const;
	public: void SetAtlasNameDisable(bool _disable);
    public: void SetAtlasEditor(void);
	public: bool IsAnimationPreviousPositionShowEnabled(void)const;
	public: void UpdateAnimationElapsedTime(float _value);
	private slots: void AnimationElapsedTimeIsChanged(double _value);
	private slots: void AnimationFPSIsChanged(double _fps);
	private slots: void AnimationDurationIsChanged(double _duration);
	private slots: void AnimationFrameDurationIsChanged(double _frameDuration);
	public: void SaveTexturedAnimation(void);
	private slots: void TexturedAnimationPositionOffsetEnable(int _enable);
	private slots: void StopAnimation(void);
	private slots: void PlayAnimation(void);
	public: void PrepareToPlayAnimation(void);
	public: void PrepareToPauseAnimation(void);
	private slots: void AnimationForwardPlayingModeEnable(bool _enable);
	private slots: void AnimationBackwardPlayingModeEnable(bool _enable);
	private slots: void AnimationPingPongPlayingModeEnable(bool _enable);
	private slots: void AnimationOnewayPlayingModeEnable(bool _enable);
	private slots: void AnimationLoopPlayingModeEnable(bool _enable);
	private slots: void AnimationSingleShotPlayingModeEnable(bool _enable);
	public: void SetAnimationCurrentFrame(int32 _index);
	private slots: void AnimationCreateAtlas(void);
	public: void ReloadAtlas(QString _name);
	public: void CreateAtlas(QString _path);
	private slots: void AnimationCurrentFrameIsChanged(int _index);
	private: void AnimationUpdateCurrentFrame(int32 _index);
    public slots: void SaveAtlasAs(void);
	public slots: void ImportAtlas(void);
	private slots: void AtlasFrameNameIsChanged(QString _name);
	private slots: void AtlasXPositionOffsetIsChanged(double _x);
	private slots: void AtlasYPositionOffsetIsChanged(double _y);
	private slots: void AtlasZPositionOffsetIsChanged(double _z);
	private slots: void AtlasNameIsChanged(QString _name);
	private slots: void AtlasFilteringIsChanged(QString _name);
	private: void SetAtlasFiltering(int32 _mode);
	private: void CreateHitboxTab(void);
	private:  void CreateVectorLerpTab(void);
	public: void SetHitbox(QString _name);
	private slots: void TextureFilteringIsChanged(QString _name);
	private: void SetTextureFiltering(int32 _mode);
	private slots: void BrushIsChanged(QString _name);
    public slots: void SaveShapeAs(void);
	private slots: void SaveShapeDialogFileFilterIsChanged(const QString& _filter);
	private slots: void ImportShapeDialogFileFilterIsChanged(const QString& _filter);
	public slots: void ImportShape(void);
    public slots: void SaveHitboxAs(void);
	public slots: void ImportHitbox(void);
	private: void CreateTileboxTab(void);
	public: void SetVectorLerp(QString _name);
	private slots: void ImportVectorLerpFloatLerp(void);
	private slots: void SaveVectorLerpFloatLerpAs(void);
	private slots: void ChangeVectorLerpAmountOfSegments(int _segments);
	private slots: void ChangeVectorLerpMode(QString _mode);
	private: int32 GetVectorLerpMode(QString _mode);
	private: int32 GetVectorLerpModeIndex(void);
	public slots: void VectorLerpSaveCurveAs(void);
	private slots: void SaveCurveDialogFileFilterIsChanged(const QString& _filter);
	public slots: void SavePointsAs(void);
	public slots: void ImportPoints(void);
    public slots: void SaveVectorLerpAs(void);
	public slots: void ImportVectorLerp(void);
	private: int32 GetVectorLerpMode(int32 _mode);
	private slots: void VectorLerpNameIsChanged(void);
	private slots: void VectorLerpFloatLerpNameIsChanged(void);
	private slots: void VectorLerpFloatLerpTIsChanged(double _value);
	private slots: void VectorLerpFloatLerpTargetIsChanged(double _value);
	private slots: void VectorLerpFloatLerpPlayingSpeedIsChanged(double _value);
	private slots: void VectorLerpFloatLerpPlayingDurationIsChanged(double _value);
	private slots: void VectorLerpFloatLerpElapsedTimeIsChanged(double _value);
	private slots: void VectorLerpFloatLerpCurrentIsChanged(double _value);
	private slots: void VectorLerpFloatLerpModeIsChanged(QString _mode);
	private: int32 GetFloatLerpModeIndex(QString _mode);
	private slots: void VectorLerpFloatLerpForwardPlayingModeEnable(bool _enable);
	private slots: void VectorLerpFloatLerpBackwardPlayingModeEnable(bool _enable);
	private slots: void VectorLerpFloatLerpPingPongPlayingModeEnable(bool _enable);
	private slots: void VectorLerpFloatLerpOnewayPlayingModeEnable(bool _enable);
	private slots: void VectorLerpFloatLerpLoopPlayingModeEnable(bool _enable);
	private slots: void VectorLerpFloatLerpSingleShotPlayingModeEnable(bool _enable);
	public: bool IsVectorLerpFloatLerpPlayingDurationSupported(void)const;
	private slots: void VectorLerpFloatLerpPlay(void);
	private slots: void VectorLerpFloatLerpStop(void);
	public: void PrepareVectorLerpFloatLerpToPlay(void);
	public: void PrepareVectorLerpFloatLerpToPause(void);
	public: void UpdateVectorLerpFloatLerpInfo(void);
	public: void UpdateVectorLerpFloatLerpElapsedTime(float _value);
	public: void SetVectorLerpFloatLerpCurrent(float _value);
	public: void SetVectorLerpFloatLerpDelta(float _value);
	public: void SetVectorLerpFloatLerpT(float _value);
	public: void SetVectorLerpCurrent(Vector3 _value);
	public: void SetVectorLerpDelta(Vector3 _value);
	public: void SetFloatLerp(QString _name);
	public slots: void ChangeSelectShape(void);
	public: void FreezeLastSelectedShape(void);
	public slots: void SetShapeLock(int _enable);
	public: void DestroyAllShapes(void);
	public: void DestroyShape(int32 _index);
	private slots: void HitboxIsChanged(int _enable);
	public slots: void CreateShape(void);
	public: void CreateShape(QString _name, int _collisionGroupIndex = 0, bool _collisionEnable = true, bool _collisionPolygonsInfoEnable = false, int _boundingVolumeType = Mesh::BOUNDING_CIRCLE);
	public slots: void RemoveSelectedShape(void);
	private slots: void ChangeBuildMode(QString _mode);
	public: void SelectShape(int32 _index);
	public: void UpdateAmountOfPoints(int32 _size);
	public slots: void CreateSubPoints(void);
	public: void PivotChangeState(bool _state);
	public slots: void ChangePivot(void);
	public slots: void ViewportCursorEnter(void);
	public slots: void ViewportCursorLeave(void);
	public: int GetSelectedShapeIndex(void)const;
	public: TextureShapeListWidget::ItemShape* GetSelectedShape(void);
	public: QString GetCurrentTabName(void)const;
	public: int32 GetCircleSegments(void)const;
	public: QString GetCurrentBrush(void)const;
	public: bool IsViewportFocus(void)const;
    public: bool IsQuadShowEnabled(void)const;
    public: bool IsVectorLerpShowCurveEnabled(void)const;
	public: bool IsShapeLocked(void)const;
	public: bool IsHitboxEnabled(void)const;
	public: QString GetCurrentBuildMode(void)const;
    public: bool IsPointsShowEnabled(void)const;
    public: bool IsLinesShowEnabled(void)const;
    public: bool IsGizmoXYShowEnabled(void)const;
    public: bool IsGridShowEnabled(void)const;
	private slots: void LoadTexture(void);
	public: void ReloadTexture(QString _path);
	public: void SetFastCreating(bool _state);
	public: void SetTexture(QString _name);
	public: void SetTexturedAnimation(QString _name);
};


#endif 

