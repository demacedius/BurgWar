RegisterClientScript()

ENTITY.IsNetworked = true

ENTITY.Properties = {
	{ Name = "friction", Type = PropertyType.Float, Default = 1 },
	{ Name = "mass", Type = PropertyType.Float, Default = 0 },
	{ Name = "size", Type = PropertyType.FloatSize },
}

function ENTITY:Initialize()
	local size = self:GetProperty("size")
	local colliderSize = size / 2
	self:SetCollider(Rect(-colliderSize, colliderSize))
	self:InitRigidBody(self:GetProperty("mass"), self:GetProperty("friction"))

	if (EDITOR) then
		self:AddSprite({
			Color = { r = 200, g = 0, b = 0, a = 180 },
			RenderOrder = 2000,
			Size = self:GetProperty("size"),
		})
	end
end