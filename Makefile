.PHONY: clean All

All:
	@echo "----------Building project:[ PostOffice - Debug ]----------"
	@cd "PostOffice" && "$(MAKE)" -f  "PostOffice.mk"
clean:
	@echo "----------Cleaning project:[ PostOffice - Debug ]----------"
	@cd "PostOffice" && "$(MAKE)" -f  "PostOffice.mk" clean
