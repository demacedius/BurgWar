RegisterClientScript("pickable_weapon_grenade.lua")

ENTITY.IsNetworked = true
ENTITY.PlayerControlled = false
ENTITY.MaxHealth = 0

ENTITY.Properties = {}

function ENTITY:Initialize()
	self:SetCollider(Circle(Vec2(0, 0) * 0.3, 128 * 0.3))
	self:EnableCollisionCallbacks(true)

	if (CLIENT) then
		self:AddSprite("grenade.png", Vec2(0.3, 0.3))
	end
end

function ENTITY:OnCollisionStart(other)
	if (SERVER and other.Name == "burger") then
		local owner = other:GetOwner()
		if (not owner:HasWeapon("weapon_grenade")) then
			owner:GiveWeapon("weapon_grenade")
			self:Kill()
			self.Parent:OnPowerupConsumed()
		end
	end

	return false
end
