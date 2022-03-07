
set(SOURCES 
	printer.c
)

target_sources(
	${PROJECT_NAME}
	PUBLIC
	${SOURCES}
)

target_sources(
	Test
	PUBLIC
	${SOURCES}
)
