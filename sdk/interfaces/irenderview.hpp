#pragma once

#include "../math/qangle.hpp"
#include "../math/vector2d.hpp"
#include "../math/vector4d.hpp"
#include "../math/matrix.hpp"

namespace sdk
{
	class CViewSetup;
	class CEngineSprite;
	class IClientEntity;
	class IMaterial;
	class IClientRenderable;
	class ITexture;

	struct model_t;

	typedef unsigned short LeafIndex_t;

	struct WorldListLeafData_t
	{
		LeafIndex_t     leafIndex;
		int16_t         waterData;
		uint16_t        firstTranslucentSurface;
		uint16_t        translucentSurfaceCount;
	};

	struct WorldListInfo_t
	{
		int                     m_ViewFogVolume;
		int                     m_LeafCount;
		bool                    m_bHasWater;
		WorldListLeafData_t*    m_pLeafDataList;
	};

	struct VisibleFogVolumeInfo_t
	{
		int         m_nVisibleFogVolume;
		int         m_nVisibleFogVolumeLeaf;
		bool        m_bEyeInFogVolume;
		float       m_flDistanceToWater;
		float       m_flWaterHeight;
		IMaterial*  m_pFogVolumeMaterial;
	};

	struct VPlane
	{
		Vector       m_Normal;
		vec_t        m_Dist;
	};

	typedef VPlane Frustum[6];

	struct BrushVertex_t
	{
		Vector      m_Pos;
		Vector      m_Normal;
		Vector      m_TangentS;
		Vector      m_TangentT;
		Vector2D    m_TexCoord;
		Vector2D    m_LightmapCoord;
	private:
		BrushVertex_t(const BrushVertex_t& src);
	};

	struct VisOverrideData_t
	{
		Vector       m_vecVisOrigin;                
		float        m_fDistToAreaPortalTolerance;  
	};

	class IBrushSurface
	{
	public:
		virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
		virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;
		virtual int  GetVertexCount() const = 0;
		virtual void GetVertexData(BrushVertex_t* pVerts) = 0;
		virtual IMaterial* GetMaterial() = 0;
	};

	class IBrushRenderer
	{
	public:
		virtual bool RenderBrushModelSurface(IClientEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
	};

	class IVRenderView
	{
	public:
		virtual void                DrawBrushModel(IClientEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool sort) = 0;
		virtual void                TouchLight(struct dlight_t *light) = 0;
		virtual void                Draw3DDebugOverlays(void) = 0;
		virtual void                SetBlend(float blend) = 0;
		virtual float               GetBlend(void) = 0;
		virtual void                SetColorModulation(float const* blend) = 0;
		virtual void                GetColorModulation(float* blend) = 0;
		virtual void                SceneBegin(void) = 0;
		virtual void                SceneEnd(void) = 0;
		virtual void                GetVisibleFogVolume(const Vector& eyePoint, VisibleFogVolumeInfo_t *pInfo) = 0;
		virtual void                DrawTopView(bool enable) = 0;
		virtual void                TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;
		virtual void                DrawLights(void) = 0;
		virtual void                DrawMaskEntities(void) = 0;
		virtual void                DrawLineFile(void) = 0;
		virtual void                ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;
		virtual bool                AreAnyLeavesVisible(int *leafList, int nLeaves) = 0;
		virtual void                VguiPaint(void) = 0;
		virtual void                ViewDrawFade(uint8_t *color, IMaterial *pMaterial) = 0;
		virtual void                OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
		virtual unsigned long       GetLightAtPoint(Vector& pos) = 0;
		virtual int                 GetViewEntity(void) = 0;
		virtual bool                IsViewEntity(int entindex) = 0;
		virtual float               GetFieldOfView(void) = 0;
		virtual unsigned char**     GetAreaBits(void) = 0;
		virtual void                SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;
		virtual void                InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;
		virtual void                DrawBrushModelShadow(IClientRenderable *pRenderable) = 0;
		virtual bool                DoesBoxIntersectWaterVolume(const Vector &mins, const Vector &maxs, int leafWaterDataID) = 0;
		virtual void                SetAreaState(unsigned char chAreaBits[32], unsigned char chAreaPortalBits[24]) = 0;
		virtual void                VGui_Paint(int mode) = 0;
		virtual void                Push3DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
		virtual void                Push2DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
		virtual void                PopView(Frustum frustumPlanes) = 0;
		virtual void                SetMainView(const Vector &vecOrigin, const QAngle &angles) = 0;
		virtual void                ViewSetupVisEx(bool novis, int numorigins, const Vector origin[], unsigned int &returnFlags) = 0;
		virtual void                OverrideViewFrustum(Frustum custom) = 0;
		virtual void                DrawBrushModelShadowDepth(IClientEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool bSort) = 0;
		virtual void                UpdateBrushModelLightmap(model_t *model, IClientRenderable *pRenderable) = 0;
		virtual void                BeginUpdateLightmaps(void) = 0;
		virtual void                EndUpdateLightmaps(void) = 0;
		virtual void                OLD_SetOffCenterProjectionMatrix(float fov, float zNear, float zFar, float flAspectRatio, float flBottom, float flTop, float flLeft, float flRight) = 0;
		virtual void                OLD_SetProjectionMatrixOrtho(float left, float top, float right, float bottom, float zNear, float zFar) = 0;
		virtual void                Push3DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes, ITexture* pDepthTexture) = 0;
		virtual void                GetMatricesForView(const CViewSetup &view, VMatrix *pWorldToView, VMatrix *pViewToProjection, VMatrix *pWorldToProjection, VMatrix *pWorldToPixels) = 0;
		inline void                 SetColorModulation(float r, float g, float b)
		{
			float clr[3] = { r, g, b };
			SetColorModulation(clr);
		}
	};
}